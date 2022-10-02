// Copyright 2022 Tim Leonard. All Rights Reserved.

#include "GBInteractWidget.h"
#include "GBJam/Utils/GBGameplayStatics.h"
#include "GBJam/UI/GBHUD.h"
#include "GBJam/Items/GBItem.h"
#include "GBJam/Interactable/GBInteractable.h"

void UGBInteractWidget::OnOpen_Implementation()
{
}

void UGBInteractWidget::OnClose_Implementation()
{
}

void UGBInteractWidget::AddInteractable(AActor* Interactable)
{
    Interactables.Add(Interactable);
    UpdateState();
}

void UGBInteractWidget::RemoveInteractable(AActor* Interactable)
{
    Interactables.Remove(Interactable);
    UpdateState();
}

AActor* UGBInteractWidget::GetFocused()
{
    if (Interactables.IsEmpty() || !CanFocus())
    {
        return nullptr;
    }
    else
    {
        return Interactables[0];
    }
}

void UGBInteractWidget::UpdateState()
{
    bool bShouldBeOpen = false;

    if (IsEquippedItemOverriding())
    {
        ContentsBox->SetText(FText::FromString(IsEquippedItemOverridePrompt()));
        bShouldBeOpen = true;        
    }
    else if (Interactables.IsEmpty() || !CanFocus())
    {
        ContentsBox->SetText(FText::FromString(""));
        bShouldBeOpen = false;
    }
    else
    {
        AActor* Actor = Interactables[0];
        IGBInteractable* Active = Cast<IGBInteractable>(Actor);
        ContentsBox->SetText(FText::FromString(Active->Execute_GetPrompt(Actor)));
        bShouldBeOpen = true;
    }

    if (bShouldBeOpen != bIsOpen)
    {
        if (bShouldBeOpen)
        {
            OnOpen();
        }
        else
        {
            OnClose();
        }
        bIsOpen = bShouldBeOpen;
    }
}

bool UGBInteractWidget::IsEquippedItemOverriding()
{
    bool bOverriding = false;
    AActor* EquippedItem = UGBGameplayStatics::GetEquippedItem(this);
    if (EquippedItem && !Interactables.IsEmpty())
    {
        AActor* Interactable = Interactables[0];
        if (Cast<IGBItem>(EquippedItem)->Execute_ShouldOverrideInteractable(EquippedItem, Interactable))
        {
            bOverriding = true;
        }
    }
    return bOverriding;
}

FString UGBInteractWidget::IsEquippedItemOverridePrompt()
{
    bool bOverriding = false;
    AActor* EquippedItem = UGBGameplayStatics::GetEquippedItem(this);
    if (EquippedItem && !Interactables.IsEmpty())
    {
        AActor* Interactable = Interactables[0];
        return Cast<IGBItem>(EquippedItem)->Execute_GetOverrideInteractablePrompt(EquippedItem, Interactable);
    }
    return "";
}

bool UGBInteractWidget::CanFocus()
{
    bool CanFocus = !UGBGameplayStatics::IsMessageBoxOpen(this);
    return CanFocus;
}

void UGBInteractWidget::Update(float InDeltaTime)
{
    UpdateState();
}