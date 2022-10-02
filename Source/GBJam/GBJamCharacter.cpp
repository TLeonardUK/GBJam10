// Copyright 2022 Tim Leonard. All Rights Reserved.

#include "GBJamCharacter.h"
#include "GBJamProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/InputSettings.h"
#include "GBJam/Utils/GBGameplayStatics.h"
#include "GBJam/Utils/GBDamageType.h"
#include "GBJam/Components/GBHealthComponent.h"
#include "GBJam/Items/GBItem.h"
#include "GBJam/UI/GBHUD.h"

AGBJamCharacter::AGBJamCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	TurnRateGamepad = 75.f;

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	ItemAttachLocationComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ItemAttachPoint"));
	ItemAttachLocationComponent->SetupAttachment(GetCapsuleComponent());
	ItemAttachLocationComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, -10.0f));
	ItemAttachLocationComponent->SetRelativeLocation(FVector(-14.772116f, 22.604723f, 45.000000f));

	HealthComponent = CreateDefaultSubobject<UGBHealthComponent>(TEXT("Health"));
	HealthComponent->MaxHealth = 3.0f;
	HealthComponent->Health = 3.0f;
}

void AGBJamCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AGBJamCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction("PrimaryAction", IE_Pressed, this, &AGBJamCharacter::OnPrimaryActionPressed);
	PlayerInputComponent->BindAction("PrimaryAction", IE_Released, this, &AGBJamCharacter::OnPrimaryActionReleased);
	PlayerInputComponent->BindAction("SecondaryAction", IE_Pressed, this, &AGBJamCharacter::OnSecondaryActionPressed);
	PlayerInputComponent->BindAction("SecondaryAction", IE_Released, this, &AGBJamCharacter::OnSecondaryActionReleased);
	PlayerInputComponent->BindAction("Start", IE_Pressed, this, &AGBJamCharacter::OnStartPressed);
	PlayerInputComponent->BindAction("Select", IE_Pressed, this, &AGBJamCharacter::OnSelectPressed);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AGBJamCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Turn Right / Left", this, &AGBJamCharacter::TurnAtRate);
}

void AGBJamCharacter::AddItem(AActor* Item, int Count)
{
	for (TPair<AActor*, int> Pair : Items)
	{
		if (Pair.Key->GetClass() == Item->GetClass())
		{
			Items[Pair.Key] += Count;
			Item->Destroy();
			return;
		}
	}

	Items.Add(Item, Count);

	IGBItem* ItemInterface = Cast<IGBItem>(Item);

	FTransform OffsetTransform = FTransform::Identity;
	OffsetTransform.SetTranslation(ItemInterface->Execute_GetAttachmentOffset(Item));

	FTransform Transform = ItemAttachLocationComponent->GetComponentTransform();
	Transform = OffsetTransform * Transform;

	Item->SetActorTransform(Transform, false, nullptr, ETeleportType::ResetPhysics);
	Item->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	Item->SetActorHiddenInGame(true);

	if (EquippedItem == nullptr)
	{
		EquipItem(Item->GetClass());
	}
}

bool AGBJamCharacter::RemoveItem(UClass* OfClass)
{
	for (TPair<AActor*, int> Pair : Items)
	{
		if (Pair.Key->GetClass() == OfClass)
		{
			if (Pair.Value > 1)
			{
				Items[Pair.Key]--;
				return true;
			}
			else
			{
				if (EquippedItem == Pair.Key)
				{
					UnequipItem();
				}
				Items.Remove(Pair.Key);
				Pair.Key->Destroy();
				return true;
			}
		}
	}
	return false;
}

bool AGBJamCharacter::EquipItem(UClass* OfClass)
{
	if (EquippedItem)
	{
		UnequipItem();
	}

	for (TPair<AActor*, int> Pair : Items)
	{
		if (Pair.Key->GetClass() == OfClass)
		{
			EquippedItem = Pair.Key;
			EquippedItem->SetActorHiddenInGame(false);
			Cast<IGBItem>(EquippedItem)->Execute_Equip(EquippedItem);
			return true;
		}
	}

	return false;
}

bool AGBJamCharacter::UnequipItem()
{
	if (EquippedItem)
	{
		EquippedItem->SetActorHiddenInGame(true);
		Cast<IGBItem>(EquippedItem)->Execute_Unequip(EquippedItem);
		EquippedItem = nullptr;
		return true;
	}
	return false;
}

int AGBJamCharacter::GetItemUsesLeft(UClass* OfClass)
{
	for (TPair<AActor*, int> Pair : Items)
	{
		if (Pair.Key->GetClass() == OfClass)
		{
			return Pair.Value;
		}
	}
	return 0;
}

int AGBJamCharacter::GetEquippedItemUsesLeft()
{
	if (EquippedItem)
	{
		return GetItemUsesLeft(EquippedItem->GetClass());
	}
	return 0;
}

AActor* AGBJamCharacter::GetEquippedItem()
{
	return EquippedItem;
}

TArray<AActor*> AGBJamCharacter::GetItems()
{
	TArray<AActor*> ItemArray;
	Items.GenerateKeyArray(ItemArray);
	return ItemArray;
}

bool AGBJamCharacter::HasItemClass(UClass* Class)
{
	for (TPair<AActor*, int> Pair : Items)
	{
		if (Pair.Key->GetClass() == Class)
		{
			return true;
		}
	}

	return false;
}

void AGBJamCharacter::OnStartPressed()
{
	if (UGBGameplayStatics::UIHasFocus(this))
	{
		return;
	}

	if (UGBGameplayStatics::GetHUD(this)->GetState() == EHUDState::InGame)
	{
		UGBGameplayStatics::GetHUD(this)->SetState(EHUDState::Pause);
	}
}

void AGBJamCharacter::OnSelectPressed()
{
	if (UGBGameplayStatics::UIHasFocus(this))
	{
		return;
	}

	if (UGBGameplayStatics::GetHUD(this)->GetState() == EHUDState::InGame)
	{
		UGBGameplayStatics::GetHUD(this)->SetState(EHUDState::Inventory);
	}
}

void AGBJamCharacter::OnPrimaryActionPressed()
{
	if (UGBGameplayStatics::UIHasFocus(this))
	{
		UGBGameplayStatics::SkipMessageBox(this);
	}
	else
	{
		bool InteractOverridden = false;

		if (EquippedItem)
		{
			AActor* Interactable = UGBGameplayStatics::GetInteractableObject(this);
			if (Cast<IGBItem>(EquippedItem)->Execute_ShouldOverrideInteractable(EquippedItem, Interactable))
			{
				InteractOverridden = true;
			}
		}

		if (!InteractOverridden && UGBGameplayStatics::IsInteractableFocused(this))
		{
			UGBGameplayStatics::InteractWithFocused(this);
		}
		else if (EquippedItem)
		{
			if (Cast<IGBItem>(EquippedItem)->Execute_Use(EquippedItem))
			{
				// If we have a limited amount of ammo, reduce it.
				if (Items[EquippedItem] > 0)
				{
					RemoveItem(EquippedItem->GetClass());
				}
			}
		}
	}
}

void AGBJamCharacter::OnPrimaryActionReleased()
{
	if (UGBGameplayStatics::UIHasFocus(this))
	{
		return;
	}

}

void AGBJamCharacter::OnSecondaryActionPressed()
{
	StrafeDown = true;
}

void AGBJamCharacter::OnSecondaryActionReleased()
{
	StrafeDown = false;
}

void AGBJamCharacter::MoveForward(float Value)
{
	if (UGBGameplayStatics::UIHasFocus(this))
	{
		return;
	}

	if (Value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AGBJamCharacter::TurnAtRate(float Value)
{
	if (UGBGameplayStatics::UIHasFocus(this))
	{
		return;
	}

	if (StrafeDown)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
	else
	{
		AddControllerYawInput(Value * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
	}
}
