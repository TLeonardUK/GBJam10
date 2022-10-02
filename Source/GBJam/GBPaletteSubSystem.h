// Copyright 2022 Tim Leonard. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Engine/DataTable.h"
#include "GBPaletteSubSystem.generated.h"

USTRUCT(BlueprintType)
struct FPalette : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor BackgroundColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor ForegroundColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor ObjectColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor HighlightColor;

public:

	static FPalette Lerp(const FPalette& Start, const FPalette& End, float Alpha);

};

/**
 * 
 */
UCLASS()
class GBJAM_API UGBPaletteSubSystem 
	: public UGameInstanceSubsystem
	, public FTickableGameObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UMaterialParameterCollection* ParameterCollection = nullptr;

public:
	UGBPaletteSubSystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	// Gets the current palette things should be rendered with.
	UFUNCTION(BlueprintCallable)
	FPalette GetActivePalette();

	// Swaps the palette instantly.
	UFUNCTION(BlueprintCallable)
	void SetPalette(FPalette NewPalette);
	
	// Flags the given palette for a duration before reverting to the old one.
	UFUNCTION(BlueprintCallable)
	void FlashPalette(FPalette NewPalette, float Duration);
	
	// Lerps between the current and given palette over time in steps.
	UFUNCTION(BlueprintCallable)
	void TransitionPalette(FPalette NewPalette, int Steps, float StepDuration);
	
public:
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;

private:
	FPalette m_currentPalette;

	FPalette m_transitionPalette;
	FPalette m_transitionOldPalette;
	int m_transitionStepsTotal;
	int m_transitionSteps;
	float m_transitionStepDuration;
	bool m_transitionInProgress = false;
	float m_transitionTimer;

	FPalette m_flashOldPalette;
	float m_flashTimer = 0.0f;

};
