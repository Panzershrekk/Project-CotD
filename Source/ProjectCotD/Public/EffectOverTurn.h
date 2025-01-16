// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "EffectOverTurn.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOTD_API UEffectOverTurn : public UGameplayEffect
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turn Duration")
	//Number of turn that is applied when applying the effect
	int32 TurnApplied;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turn Duration")
	//Turn before the effect is gone
	int32 TurnRemaining;
};
