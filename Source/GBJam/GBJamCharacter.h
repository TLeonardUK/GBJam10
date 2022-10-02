// Copyright 2022 Tim Leonard. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GBJamCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;
class UGBHealthComponent;

// Declaration of the delegate that will be called when the Primary Action is triggered
// It is declared as dynamic so it can be accessed also in Blueprints
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUseItem);

UCLASS(config=Game)
class AGBJamCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
	UGBHealthComponent* HealthComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
	UArrowComponent* ItemAttachLocationComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float TurnRateGamepad;

public:
	AGBJamCharacter();

	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	UFUNCTION(BlueprintCallable)
	void AddItem(AActor* Item, int Count);

	UFUNCTION(BlueprintCallable)
	bool RemoveItem(UClass* OfClass);

	UFUNCTION(BlueprintCallable)
	bool EquipItem(UClass* OfClass);

	UFUNCTION(BlueprintCallable)
	bool UnequipItem();
	
	UFUNCTION(BlueprintCallable)
	int GetItemUsesLeft(UClass* OfClass);
	
	UFUNCTION(BlueprintCallable)
	int GetEquippedItemUsesLeft();

	UFUNCTION(BlueprintCallable)
	AActor* GetEquippedItem();
	
	UFUNCTION(BlueprintCallable)
	TArray<AActor*> GetItems();
	
	UFUNCTION(BlueprintCallable)
	bool HasItemClass(UClass* Class);
	
protected:
	virtual void BeginPlay();

	void OnPrimaryActionPressed();
	void OnPrimaryActionReleased();
	void OnSecondaryActionPressed();
	void OnSecondaryActionReleased();

	void OnStartPressed();
	void OnSelectPressed();

	void MoveForward(float Val);
	void MoveRight(float Val);
	void TurnAtRate(float Rate);
	
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

private:
	bool StrafeDown = false;

	UPROPERTY()
	TMap<AActor*, int> Items;

	AActor* EquippedItem = nullptr;

};

