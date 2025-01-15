// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamagerTypes.h"
#include "GameplayEffect.h"
#include "GameplayEffectStatusChange.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOTD_API UGameplayEffectStatusChange : public UGameplayEffect
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Other")
	FDamagerInfo DamagerInfo;
};
