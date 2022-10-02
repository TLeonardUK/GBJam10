// Copyright 2022 Tim Leonard. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GBInteractable.generated.h"

UINTERFACE(BlueprintType)
class UGBInteractable : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IGBInteractable
{
	GENERATED_IINTERFACE_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Interact();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FString GetPrompt();

};