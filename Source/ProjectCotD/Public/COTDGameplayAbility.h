// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	class UAbilitiesDataAsset* AbilitiesDataAsset;
};
