// Copyright 2022 Tim Leonard. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "GBInteractWidget.generated.h"

UCLASS()
class UGBInteractWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	/** Block that text is shown within. */
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ContentsBox;

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnOpen();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnClose();

	UFUNCTION(BlueprintCallable)
	void AddInteractable(AActor* Interactable);
	
	UFUNCTION(BlueprintCallable)
	void RemoveInteractable(AActor* Interactable);
    
	UFUNCTION(BlueprintCallable)
	AActor* GetFocused();

	UFUNCTION(BlueprintCallable)
	void Update(float InDeltaTime);

private:

	void UpdateState();

	bool CanFocus();

	bool IsEquippedItemOverriding();
	FString IsEquippedItemOverridePrompt();

private:

	UPROPERTY()
	TArray<AActor*> Interactables;

	bool bIsOpen = false;


};