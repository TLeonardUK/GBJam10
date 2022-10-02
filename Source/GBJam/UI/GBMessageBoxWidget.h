// Copyright 2022 Tim Leonard. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "GBMessageBoxWidget.generated.h"

UENUM()
enum class EGBMessageBoxState
{
	Opening,
	Typing,
	Waiting,
	Closing,
	Closed
};

UCLASS()
class UGBMessageBoxWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	/** Block that text is shown within. */
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ContentsBox;

	UPROPERTY(BlueprintReadWrite)
	float OpenTime = 0.25f;

	UPROPERTY(BlueprintReadWrite)
	float CloseTime = 0.25f;

	UPROPERTY(BlueprintReadWrite)
	float TypeTime = 0.07f;

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnOpening();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnClosing();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnType();

	UFUNCTION(BlueprintCallable)
	bool IsOpen();
	
	UFUNCTION(BlueprintCallable)
	void Show(const FString& Message);
    
	UFUNCTION(BlueprintCallable)
	void Skip();

	UFUNCTION(BlueprintCallable)
	void Update(float InDeltaTime);

private:

	void ChangeState(EGBMessageBoxState NewState);

	void StartNextMessage();
    
private:
	EGBMessageBoxState State = EGBMessageBoxState::Closed;
	float StateTimer = 0.0f;
	float TypeTimer = 0.0f;
	int CharactersTyped = 0;

	TQueue<FString> MessageQueue;

	FString FullMessage = "";
	FString ShownMessage = "";


};