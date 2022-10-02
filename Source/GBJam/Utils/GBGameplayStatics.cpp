// Copyright 2022 Tim Leonard. All Rights Reserved.

#include "GBGameplayStatics.h"
#include "Components/PrimitiveComponent.h"
#include "DrawDebugHelpers.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Engine/World.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Kismet/GameplayStatics.h"
#include "GBJam/UI/GBHUD.h"
#include "GBJam/UI/GBHUDWidget.h"
#include "GBJam/UI/GBMessageBoxWidget.h"
#include "GBJam/UI/GBInteractWidget.h"
#include "GBJam/GBJamCharacter.h"
#include "GBJam/Interactable/GBInteractable.h"

UGBGameplayStatics::UGBGameplayStatics(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

AGBHUD* UGBGameplayStatics::GetHUD(const UObject* WorldContextObject)
{
	return Cast<AGBHUD>(UGameplayStatics::GetPlayerController(WorldContextObject, 0)->GetHUD());;
}

void UGBGameplayStatics::ShowMessageBox(const UObject* WorldContextObject, const FString& Message)
{
	AGBHUD* hud = GetHUD(WorldContextObject);
	hud->GetRoot()->MessageBox->Show(Message);
}

void UGBGameplayStatics::SkipMessageBox(const UObject* WorldContextObject)
{
	AGBHUD* hud = GetHUD(WorldContextObject);
	hud->GetRoot()->MessageBox->Skip();
}

bool UGBGameplayStatics::IsMessageBoxOpen(const UObject* WorldContextObject)
{
	AGBHUD* hud = GetHUD(WorldContextObject);
	return hud->GetRoot()->MessageBox->IsOpen();
}

bool UGBGameplayStatics::UIHasFocus(const UObject* WorldContextObject)
{
	AGBHUD* hud = GetHUD(WorldContextObject);
	return hud->HasFocus();
}

void UGBGameplayStatics::AddInteractable(const UObject* WorldContextObject, AActor* Object)
{
	AGBHUD* hud = GetHUD(WorldContextObject);
	hud->GetRoot()->InteractBox->AddInteractable(Object);
}

void UGBGameplayStatics::RemoveInteractable(const UObject* WorldContextObject, AActor* Object)
{
	AGBHUD* hud = GetHUD(WorldContextObject);
	hud->GetRoot()->InteractBox->RemoveInteractable(Object);
}

bool UGBGameplayStatics::IsInteractableFocused(const UObject* WorldContextObject)
{
	AGBHUD* hud = GetHUD(WorldContextObject);
	return hud->GetRoot()->InteractBox->GetFocused() != nullptr;
}

void UGBGameplayStatics::InteractWithFocused(const UObject* WorldContextObject)
{
	AGBHUD* hud = GetHUD(WorldContextObject);
	AActor* actor = hud->GetRoot()->InteractBox->GetFocused();
	IGBInteractable* interactable = Cast<IGBInteractable>(actor);
	interactable->Execute_Interact(actor);
}

AActor* UGBGameplayStatics::GetInteractableObject(const UObject* WorldContextObject)
{
	AGBHUD* hud = GetHUD(WorldContextObject);
	return hud->GetRoot()->InteractBox->GetFocused();
}

AActor* UGBGameplayStatics::GetEquippedItem(const UObject* WorldContextObject)
{
	AGBJamCharacter* character = Cast<AGBJamCharacter>(UGameplayStatics::GetPlayerCharacter(WorldContextObject, 0));
	if (character)
	{
		return character->GetEquippedItem();
	}
	return nullptr;
}

bool UGBGameplayStatics::HasItemClass(const UObject* WorldContextObject, UClass* Class)
{
	AGBJamCharacter* character = Cast<AGBJamCharacter>(UGameplayStatics::GetPlayerCharacter(WorldContextObject, 0));
	if (character)
	{
		return character->HasItemClass(Class);
	}
	return nullptr;
}