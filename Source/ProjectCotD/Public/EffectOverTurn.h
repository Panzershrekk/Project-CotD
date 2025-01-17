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
	//Wether or not the calculation class should be triggered when applied, for a stats buff for exemple, you will want to apply it immediately
	//For bleeding effect or damage over turn, you may not want to apply the Calculation class immediately
	bool bTriggerCalculationClassOnApply = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turn Duration")
	//Number of turn that is applied when applying the effect
	int32 TurnApplied;
	//Turn before the effect is gone
	mutable int32 TurnRemaining;

public:
	void Setup() const;
	//Remove 1 Turn from effect
	int32 DecreaseTurnRemaining();

	UFUNCTION(BlueprintCallable, Category = "Turn Duration")
	int32 GetTurnRemaining() const
	{
		return TurnRemaining;
	}

};
