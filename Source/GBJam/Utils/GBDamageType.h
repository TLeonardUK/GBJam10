// Copyright 2022 Tim Leonard. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GBDamageType.generated.h"

/** Base damage type. */
UCLASS()
class UGBDamageType : public UDamageType
{
    GENERATED_BODY()

public:
    UGBDamageType();

};

/** Damage done by enemy being near */
UCLASS()
class UGBDamageType_Enemy : public UGBDamageType
{
    GENERATED_BODY()

public:

};

/** Healing damage rather than causing it. */
UCLASS()
class UGBDamageType_Heal : public UGBDamageType
{
    GENERATED_BODY()

public:

};
