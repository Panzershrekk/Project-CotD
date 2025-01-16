// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "EffectOverTurn.h"
#include "DynamicStatsChangeExecution.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOTD_API UDynamicStatsChangeExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
    /*FDamageOriginInformations mutable Info;*/
    UDynamicStatsChangeExecution();

    virtual void Execute_Implementation(
        const FGameplayEffectCustomExecutionParameters& ExecutionParams,
        FGameplayEffectCustomExecutionOutput& OutExecutionOutput
    ) const override;
};
