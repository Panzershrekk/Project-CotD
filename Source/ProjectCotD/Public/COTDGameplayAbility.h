// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitiesDataAsset.h"
#include "COTDAbilitySystemComponent.h"
#include "EffectOverTurn.h"
#include "AuraRadiusActor.h"
#include "GameplayEffectAura.h"
#include "Abilities/GameplayAbility.h"
#include "COTDGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOTD_API UCOTDGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Stats")
	UAbilitiesDataAsset* AbilitiesDataAsset;
};
