// Copyright 2022 Tim Leonard. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "GBHUD.generated.h"

class UGBHUDWidget;

UENUM(BlueprintType)
enum class EHUDState : uint8
{
	Unset,
	TitleScreen,
	InGame,
	GameOver,
	Pause,
	Inventory,
	GameComplete
};

UCLASS()
class AGBHUD : public AHUD
{
	GENERATED_BODY()

protected:
	
	/** Main widget to show in HUD. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGBHUDWidget> MainWidgetClass;
    
	/** Main widget to show for game over. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> GameOverWidgetClass;
    
	/** Main widget to show for game complete. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> GameCompleteWidgetClass;
    
	/** Main widget to show for title screen. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> TitleScreenWidgetClass;
	
	/** Main widget to show for inventory screen. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> InventoryWidgetClass;
    
	/** Main widget to show for pause screen. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> PauseWidgetClass;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool StartAtTitleScreenInEditor = false;

public:

    AGBHUD(const FObjectInitializer& ObjectInitializer);

	UGBHUDWidget* GetRoot();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnStateChanged(EHUDState InState);

	UFUNCTION(BlueprintCallable)
	void SetState(EHUDState State);
	
	UFUNCTION(BlueprintCallable)
	EHUDState GetState();

	UFUNCTION(BlueprintCallable)
	bool HasFocus();

	UFUNCTION(BlueprintCallable)
	void TakeFocus();

	UFUNCTION(BlueprintCallable)
	void ReleaseFocus();
	
	UFUNCTION(BlueprintCallable)
	void ReleaseAllFocus();

protected:


	// Begin AActor Interface
	virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;
	// End AActor Interface

private:

    UPROPERTY()
	UGBHUDWidget* RootWidget;

	UPROPERTY()
	UUserWidget* TitleScreenWidget;
	
	UPROPERTY()
	UUserWidget* GameOverWidget;

	UPROPERTY()
	UUserWidget* GameCompleteWidget;
	
	UPROPERTY()
	UUserWidget* PauseWidget;

	UPROPERTY()
	UUserWidget* InventoryWidget;

	EHUDState State = EHUDState::Unset;

	int TakenFocusCount = 0;

};

