// Copyright 2022 Tim Leonard. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GBGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GBJAM_API UGBGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite)
	FString CurrentLocation = "";

public:
	virtual void Init() override;
	
};
