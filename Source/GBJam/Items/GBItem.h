// Copyright 2022 Tim Leonard. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GBItem.generated.h"

UINTERFACE(BlueprintType)
class UGBItem : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IGBItem
{
	GENERATED_IINTERFACE_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool Use();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Equip();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Unequip();	

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FVector GetAttachmentOffset();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FString GetName();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FString GetDescription();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UMaterialInterface* GetIcon();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool ShouldOverrideInteractable(AActor* Other);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FString GetOverrideInteractablePrompt(AActor* Other);

};