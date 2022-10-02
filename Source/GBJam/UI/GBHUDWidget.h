// Copyright 2022 Tim Leonard. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h"
#include "GBHUDWidget.generated.h"

class UGBMessageBoxWidget;
class UGBInteractWidget;

UCLASS()
class UGBHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	/** Message box widget */
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UGBMessageBoxWidget* MessageBox;
	
	/** Message box widget */
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UGBInteractWidget* InteractBox;

};