// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamagerTypes.h"
#include "GameplayEffect.h"
#include "GameplayEffectDamageOverTurn.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOTD_API UGameplayEffectDamageOverTurn : public UGameplayEffect
{
	GENERATED_BODY()
public:
	FDamagerInfo DamagerInfo;
};
