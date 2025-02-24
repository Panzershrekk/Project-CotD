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
	//Wether or not the calculation should trigger on remove
	bool bTriggerCalculationClassOnRemove = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turn Duration")
	//Wether or not the calculation class should be triggered at the start of everyturn
	//For bleeding effect or damage over turn, you may want to trigger every turn
	bool bTriggerCalculationAtTherStartOfEveryTurn = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turn Duration")
	//Number of turn that is applied when applying the effect, -1 is permanent
	int32 TurnApplied;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Estetic")
	//Icon of the effect
	UTexture2D*  Icon;

public:
	//TBD
};
