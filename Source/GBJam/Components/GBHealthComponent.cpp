// Copyright 2022 Tim Leonard. All Rights Reserved.

#include "GBHealthComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "Components/PrimitiveComponent.h"
#include "GBJam/Utils/GBDamageType.h"
#include "CollisionQueryParams.h"

UGBHealthComponent::UGBHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

    Health = MaxHealth;
}

void UGBHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    AActor* OwnerActor = GetOwner();
    OwnerActor->OnTakeAnyDamage.AddDynamic(this, &UGBHealthComponent::OnOwnerDamaged);
}

void UGBHealthComponent::OnOwnerDamaged(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
    /*UE_LOG(LogTemp, Log, TEXT("UGBHealthComponent::OnOwnerDamaged: Actor=%s Damage=%f InstigatedBy=%s Causer=%s DamageType=%s"),
        *DamagedActor->GetName(),
        Damage,
        *InstigatedBy->GetName(),
        *DamageCauser->GetName(),
        *DamageType->GetClass()->GetName()
    );*/

    FPointDamageEvent Event;
    Event.DamageTypeClass = DamageType->GetClass();
    Event.Damage = Damage;
    Event.ShotDirection = FVector::ZeroVector;

    ApplyDamage(Event);
}

void UGBHealthComponent::ApplyDamage(const FDamageEvent& DamageEvent)
{
    UDamageType const* const DamageTypeCDO = DamageEvent.DamageTypeClass ? DamageEvent.DamageTypeClass->GetDefaultObject<UDamageType>() : GetDefault<UDamageType>();
    if (DamageEvent.IsOfType(FPointDamageEvent::ClassID))
    {
        FPointDamageEvent const* const PointDamageEvent = (FPointDamageEvent*)(&DamageEvent);
        ApplyPointDamage(PointDamageEvent);
    }
    else if (DamageEvent.IsOfType(FRadialDamageEvent::ClassID))
    {
        FRadialDamageEvent const* const RadialDamageEvent = (FRadialDamageEvent*)(&DamageEvent);
        ApplyRadialDamage(RadialDamageEvent);
    }
}

void UGBHealthComponent::Heal(float Amount)
{
    FPointDamageEvent Event;
    Event.DamageTypeClass = UGBDamageType_Heal::StaticClass();
    Event.Damage = -Amount;
    Event.ShotDirection = FVector::ZeroVector;
    ApplyDamage(Event);
}

void UGBHealthComponent::ApplyScalarDamage(const FDamageEvent& DamageEvent, float Damage)
{
    if (Health <= 0.0f)
    {
        return;
    }

    float HealthOld = Health;
    Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
    float HealthDelta = (Health - HealthOld);

    UE_LOG(LogTemp, Log, TEXT("UGBHealthComponent::ApplyScalarDamage: Damage=%f Health=%f"),
        Damage,
        Health
    );

    if (Damage > 0.0f)
    {
        OnDamageDelegate.Broadcast(this, DamageEvent);
        if (Health <= 0.0f)
        {
            OnDeathDelegate.Broadcast(this, DamageEvent);
        }
    }
    else if (Damage < 0.0f)
    {
        OnHealDelegate.Broadcast(this, DamageEvent);
    }
}

void UGBHealthComponent::ApplyPointDamage(const FPointDamageEvent* Event)
{
    ApplyScalarDamage(*Event, Event->Damage);
}

void UGBHealthComponent::ApplyRadialDamage(const FRadialDamageEvent* Event)
{
    ApplyScalarDamage(*Event, Event->Params.BaseDamage);
}