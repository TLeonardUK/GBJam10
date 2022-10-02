// Copyright 2022 Tim Leonard. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "GBGameplayStatics.generated.h"

UCLASS()
class UGBGameplayStatics : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:

	// Core hud
	UFUNCTION(BlueprintCallable, Category = "UI", meta = (WorldContext = "WorldContextObject"))
	static AGBHUD* GetHUD(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable, Category = "UI", meta = (WorldContext = "WorldContextObject"))
	static bool UIHasFocus(const UObject* WorldContextObject);

	// Message box
	UFUNCTION(BlueprintCallable, Category = "UI", meta = (WorldContext = "WorldContextObject"))
	static void ShowMessageBox(const UObject* WorldContextObject, const FString& Message);
	
	UFUNCTION(BlueprintCallable, Category = "UI", meta = (WorldContext = "WorldContextObject"))
	static void SkipMessageBox(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable, Category = "UI", meta = (WorldContext = "WorldContextObject"))
	static bool IsMessageBoxOpen(const UObject* WorldContextObject);

	// Interaction
	UFUNCTION(BlueprintCallable, Category = "UI", meta = (WorldContext = "WorldContextObject"))
	static void AddInteractable(const UObject* WorldContextObject, AActor* Object);
	
	UFUNCTION(BlueprintCallable, Category = "UI", meta = (WorldContext = "WorldContextObject"))
	static void RemoveInteractable(const UObject* WorldContextObject, AActor* Object);

	UFUNCTION(BlueprintCallable, Category = "UI", meta = (WorldContext = "WorldContextObject"))
	static bool IsInteractableFocused(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable, Category = "UI", meta = (WorldContext = "WorldContextObject"))
	static void InteractWithFocused(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable, Category = "UI", meta = (WorldContext = "WorldContextObject"))
	static AActor* GetInteractableObject(const UObject* WorldContextObject);

	// Player
	UFUNCTION(BlueprintCallable, Category = "UI", meta = (WorldContext = "WorldContextObject"))
	static AActor* GetEquippedItem(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "UI", meta = (WorldContext = "WorldContextObject"))
	static bool HasItemClass(const UObject* WorldContextObject, UClass* Class);

};