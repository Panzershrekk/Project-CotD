// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "COTDUtils.h"
#include "GameplayEffectExecutionCalculation.h"
#include "DOTEffectExecutionCalculation.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOTD_API UDOTEffectExecutionCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public: 
    FDamageOriginInformations mutable Info;
    UDOTEffectExecutionCalculation();

    virtual void Execute_Implementation(
        const FGameplayEffectCustomExecutionParameters& ExecutionParams,
        FGameplayEffectCustomExecutionOutput& OutExecutionOutput
    ) const override;

    void OnHealthChanged(const FOnAttributeChangeData& Data) const;
};
