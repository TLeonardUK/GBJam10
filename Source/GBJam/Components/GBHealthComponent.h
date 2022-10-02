// Copyright 2022 Tim Leonard. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GBHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGBHealthComponentOnDeathDelegate, UGBHealthComponent*, HealthComponent, const FDamageEvent&, DamageEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGBHealthComponentOnDamageDelegate, UGBHealthComponent*, HealthComponent, const FDamageEvent&, DamageEvent);

struct FDamageEvent;

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Health), meta = (BlueprintSpawnableComponent))
class UGBHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:

    UPROPERTY(BlueprintAssignable)
    FGBHealthComponentOnDeathDelegate OnDeathDelegate;

    UPROPERTY(BlueprintAssignable)
    FGBHealthComponentOnDamageDelegate OnDamageDelegate;
    
    UPROPERTY(BlueprintAssignable)
    FGBHealthComponentOnDamageDelegate OnHealDelegate;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
	float Health = 100.0f;

public:
    UGBHealthComponent();

    UFUNCTION(BlueprintCallable)
    void ApplyDamage(const FDamageEvent& DamageEvent);
    
    UFUNCTION(BlueprintCallable)
    void Heal(float Heal);

public:

    // Start ActorComponent Interface
    virtual void BeginPlay() override;
    // End ActorComponent Interface

private:
    
    UFUNCTION()
    void OnOwnerDamaged(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

    void ApplyScalarDamage(const FDamageEvent& DamageEvent, float Damage);
    void ApplyPointDamage(const FPointDamageEvent* DamageEvent);
    void ApplyRadialDamage(const FRadialDamageEvent* DamageEvent);

};



