// Copyright 2022 Tim Leonard. All Rights Reserved.

#include "GBPaletteSubSystem.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"

FPalette FPalette::Lerp(const FPalette& Start, const FPalette& End, float Alpha)
{
    FPalette Result;
    Result.BackgroundColor = FLinearColor::LerpUsingHSV(Start.BackgroundColor, End.BackgroundColor, Alpha);
    Result.ForegroundColor = FLinearColor::LerpUsingHSV(Start.ForegroundColor, End.ForegroundColor, Alpha);
    Result.ObjectColor = FLinearColor::LerpUsingHSV(Start.ObjectColor, End.ObjectColor, Alpha);
    Result.HighlightColor = FLinearColor::LerpUsingHSV(Start.HighlightColor, End.HighlightColor, Alpha);
    return Result;
}

UGBPaletteSubSystem::UGBPaletteSubSystem()
{
    // Grab material parameter collection.
    ConstructorHelpers::FObjectFinder<UMaterialParameterCollection> objectType(TEXT("/Game/GBJam/Palette/MPC_ActivePalette"));
    if (objectType.Succeeded())
    {
        ParameterCollection = objectType.Object;
    }
}

void UGBPaletteSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
    m_currentPalette.BackgroundColor = FLinearColor(0.022174f, 0.013702f, 0.048172f);
    m_currentPalette.ForegroundColor = FLinearColor(0.127438f, 0.630757f, 0.47932f);
    m_currentPalette.ObjectColor = FLinearColor(0.261656f, 0.630757f, 0.127438f);
    m_currentPalette.HighlightColor = FLinearColor(0.745404f, 0.013702f, 0.049707f);
}

FPalette UGBPaletteSubSystem::GetActivePalette()
{
    return m_currentPalette;
}

void UGBPaletteSubSystem::Tick(float DeltaTime)
{
    if (!GetWorld())
    {
        return;
    }

    // Update transition.
    if (m_transitionInProgress)
    {
        m_transitionTimer += DeltaTime;
        if (m_transitionTimer > m_transitionStepDuration)
        {
            m_transitionTimer -= m_transitionStepDuration;
            m_transitionSteps++;

            if (m_transitionSteps >= m_transitionStepsTotal)
            {
                m_transitionInProgress = false;
            }
        }

        float alpha = m_transitionSteps / static_cast<float>(m_transitionStepsTotal);
        m_currentPalette = FPalette::Lerp(m_transitionOldPalette, m_transitionPalette, alpha);
    }

    // Flash palette.
    if (m_flashTimer > 0.0f)
    {
        m_flashTimer -= DeltaTime;
        if (m_flashTimer <= 0.0f)
        {
            m_currentPalette = m_flashOldPalette;
        }
    }

    // Apply palette to property collection.
    UMaterialParameterCollectionInstance* Instance = GetWorld()->GetParameterCollectionInstance(ParameterCollection);
    if (Instance)
    {
        Instance->SetVectorParameterValue(FName("Background"), m_currentPalette.BackgroundColor);
        Instance->SetVectorParameterValue(FName("Foreground"), m_currentPalette.ForegroundColor);
        Instance->SetVectorParameterValue(FName("Object"), m_currentPalette.ObjectColor);
        Instance->SetVectorParameterValue(FName("Highlight"), m_currentPalette.HighlightColor);
    }
}

void UGBPaletteSubSystem::SetPalette(FPalette NewPalette)
{
    // Truncate any active flash.
    m_flashTimer = 0.0f;
    
    m_currentPalette = NewPalette;
}

void UGBPaletteSubSystem::FlashPalette(FPalette NewPalette, float Duration)
{
    m_flashOldPalette = m_currentPalette;
    m_currentPalette = NewPalette;
    m_flashTimer = Duration;
}

void UGBPaletteSubSystem::TransitionPalette(FPalette NewPalette, int Steps, float StepDuration)
{
    // Truncate any active flash.
    if (m_flashTimer > 0.0f)
    {
        m_flashTimer = 0.0f;
        m_currentPalette = m_flashOldPalette;
    }

    m_transitionOldPalette = m_currentPalette;
    m_transitionPalette = NewPalette;
    m_transitionStepsTotal = Steps;
    m_transitionSteps = 0;
    m_transitionStepDuration = StepDuration;
    m_transitionTimer = 0.0f;
    m_transitionInProgress = true;
}

TStatId UGBPaletteSubSystem::GetStatId() const
{
    RETURN_QUICK_DECLARE_CYCLE_STAT(UGBPaletteSubSystem, STATGROUP_Tickables);
}


