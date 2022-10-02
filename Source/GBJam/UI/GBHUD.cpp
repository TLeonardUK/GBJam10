// Copyright 2022 Tim Leonard. All Rights Reserved.

#include "GBHUD.h"
#include "GBJam/GBJamCharacter.h"
#include "GBJam/UI/GBHUDWidget.h"
#include "Kismet/GameplayStatics.h"

AGBHUD::AGBHUD(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bTickEvenWhenPaused = true;
    //bAllowTickBeforeBeginPlay = true;
    PrimaryActorTick.TickGroup = TG_PrePhysics;
}

UGBHUDWidget* AGBHUD::GetRoot()
{
    return RootWidget;
}

void AGBHUD::BeginPlay()
{
    Super::BeginPlay();

    AGBJamCharacter* Player = Cast<AGBJamCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	ensure(Player);

	RootWidget = Cast<UGBHUDWidget>(UUserWidget::CreateWidgetInstance(*GetWorld(), MainWidgetClass, NAME_None));
    RootWidget->AddToViewport(1);

    if (State == EHUDState::Unset)
    {
        if (GetWorld()->WorldType == EWorldType::Game ||
            StartAtTitleScreenInEditor)
        {
            SetState(EHUDState::TitleScreen);
        }
        else
        {
            SetState(EHUDState::InGame);
        }
    }
}

void AGBHUD::OnStateChanged_Implementation(EHUDState InState)
{
}

void AGBHUD::SetState(EHUDState NewState)
{
    if (State == NewState)
    {
        return;
    }

    State = NewState;

    // Add/Remove Titlescreen widget
    if (State == EHUDState::TitleScreen)
    {
        TitleScreenWidget = Cast<UUserWidget>(UUserWidget::CreateWidgetInstance(*GetWorld(), TitleScreenWidgetClass, NAME_None));
        TitleScreenWidget->AddToViewport(2);
    }
    else
    {
        if (TitleScreenWidget != nullptr)
        {
            TitleScreenWidget->RemoveFromViewport();
            TitleScreenWidget = nullptr;
        }
    }

    // Add/Remove Gameover widget
    if (State == EHUDState::GameOver)
    {
        GameOverWidget = Cast<UUserWidget>(UUserWidget::CreateWidgetInstance(*GetWorld(), GameOverWidgetClass, NAME_None));
        GameOverWidget->AddToViewport(2);
    }
    else
    {
        if (GameOverWidget != nullptr)
        {
            GameOverWidget->RemoveFromViewport();
            GameOverWidget->ConditionalBeginDestroy();
            GameOverWidget = nullptr;
        }
    }

    // Add/Remove Game complete widget
    if (State == EHUDState::GameComplete)
    {
        GameCompleteWidget = Cast<UUserWidget>(UUserWidget::CreateWidgetInstance(*GetWorld(), GameCompleteWidgetClass, NAME_None));
        GameCompleteWidget->AddToViewport(2);
    }
    else
    {
        if (GameCompleteWidget != nullptr)
        {
            GameCompleteWidget->RemoveFromViewport();
            GameCompleteWidget->ConditionalBeginDestroy();
            GameCompleteWidget = nullptr;
        }
    }

    // Add/Remove pause widget
    if (State == EHUDState::Pause)
    {
        PauseWidget = Cast<UUserWidget>(UUserWidget::CreateWidgetInstance(*GetWorld(), PauseWidgetClass, NAME_None));
        PauseWidget->AddToViewport(2);
    }
    else
    {
        if (PauseWidget != nullptr)
        {
            PauseWidget->RemoveFromViewport();
            PauseWidget->ConditionalBeginDestroy();
            PauseWidget = nullptr;
        }
    }

    // Add/Remove inventory widget
    if (State == EHUDState::Inventory)
    {
        InventoryWidget = Cast<UUserWidget>(UUserWidget::CreateWidgetInstance(*GetWorld(), InventoryWidgetClass, NAME_None));
        InventoryWidget->AddToViewport(2);
    }
    else
    {
        if (InventoryWidget != nullptr)
        {
            InventoryWidget->RemoveFromViewport();
            InventoryWidget->ConditionalBeginDestroy();
            InventoryWidget = nullptr;
        }
    }

    OnStateChanged(State);
}

EHUDState AGBHUD::GetState()
{
    return State;
}

void AGBHUD::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

}

bool AGBHUD::HasFocus()
{
    return (TakenFocusCount > 0);
}

void AGBHUD::TakeFocus()
{
    TakenFocusCount++;
}

void AGBHUD::ReleaseFocus()
{
    TakenFocusCount--;
}

void AGBHUD::ReleaseAllFocus()
{
    TakenFocusCount = 0;
}