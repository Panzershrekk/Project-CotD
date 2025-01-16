// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamagerTypes.h"
#include "EffectOverTurn.h"
#include "GameplayEffectDamageOverTurn.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOTD_API UGameplayEffectDamageOverTurn : public UEffectOverTurn
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Other")
	FDamagerInfo DamagerInfo;
};
