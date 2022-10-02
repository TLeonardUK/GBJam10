// Copyright 2022 Tim Leonard. All Rights Reserved.

#include "GBMessageBoxWidget.h"
#include "GBJam/Utils/GBGameplayStatics.h"
#include "GBJam/UI/GBHUD.h"

void UGBMessageBoxWidget::OnOpening_Implementation()
{
}

void UGBMessageBoxWidget::OnClosing_Implementation()
{
}

void UGBMessageBoxWidget::OnType_Implementation()
{
}

bool UGBMessageBoxWidget::IsOpen()
{
    return (State != EGBMessageBoxState::Closed);
}

void UGBMessageBoxWidget::Show(const FString& Message)
{
    MessageQueue.Enqueue(Message);

    if (!IsOpen())
    {
        StartNextMessage();
    }
}

void UGBMessageBoxWidget::StartNextMessage()
{
    if (State == EGBMessageBoxState::Closed)
    {
        UGBGameplayStatics::GetHUD(this)->TakeFocus();
    }

    if (State == EGBMessageBoxState::Waiting)
    {
        ChangeState(EGBMessageBoxState::Typing);
    }
    else
    {
        ChangeState(EGBMessageBoxState::Opening);
    }

    FullMessage = *MessageQueue.Peek();
    ShownMessage = "";
    CharactersTyped = 0;
    TypeTimer = 0.0f;

    MessageQueue.Pop();

    if (State == EGBMessageBoxState::Opening)
    {
        OnOpening();
    }
}

void UGBMessageBoxWidget::Skip()
{
    if (State == EGBMessageBoxState::Waiting)
    {
        if (!MessageQueue.IsEmpty())
        {
            StartNextMessage();
        }
        else
        {
            OnClosing();
            ChangeState(EGBMessageBoxState::Closing);
        }
    }
    else if (State == EGBMessageBoxState::Typing)
    {
        ShownMessage = FullMessage;
        ChangeState(EGBMessageBoxState::Waiting);
    }
}

void UGBMessageBoxWidget::ChangeState(EGBMessageBoxState NewState)
{
    State = NewState;
    StateTimer = 0.0f;
}

void UGBMessageBoxWidget::Update(float InDeltaTime)
{
    StateTimer += InDeltaTime;
    switch (State)
    {
        case EGBMessageBoxState::Opening:
        {
            if (StateTimer >= OpenTime)
            {
                ChangeState(EGBMessageBoxState::Typing);
            }
            break;
        }
        case EGBMessageBoxState::Typing:
        {
            TypeTimer += InDeltaTime;
            while (TypeTimer > TypeTime && CharactersTyped < FullMessage.Len())
            {
                OnType();
                TypeTimer -= TypeTime;
                CharactersTyped++;
    
                ShownMessage = FullMessage.Mid(0, CharactersTyped);
            }

            if (CharactersTyped >= FullMessage.Len())
            {
                ChangeState(EGBMessageBoxState::Waiting);
            }
            break;
        }
        case EGBMessageBoxState::Waiting:
        {
            // Waiting on input.
            break;
        }
        case EGBMessageBoxState::Closing:
        {
            if (StateTimer >= CloseTime)
            {
                if (!MessageQueue.IsEmpty())
                {
                    StartNextMessage();
                }
                else
                {
                    UGBGameplayStatics::GetHUD(this)->ReleaseFocus();
                    ChangeState(EGBMessageBoxState::Closed);
                }
            }
            break;
        }
        case EGBMessageBoxState::Closed:
        {
            break;
        }
    }

    ContentsBox->SetText(FText::FromString(ShownMessage));
}