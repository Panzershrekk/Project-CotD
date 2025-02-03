// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EffectOverTurn.h"
#include "GameplayEffectAura.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOTD_API UGameplayEffectAura : public UEffectOverTurn
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AuraStats")
	float AuraRadius = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AuraStats")
	TArray<TSubclassOf<UGameplayEffect>> EffectsToApplyWithAura;
};
