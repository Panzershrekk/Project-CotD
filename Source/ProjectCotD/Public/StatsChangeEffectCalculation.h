// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "StatsChangeEffectCalculation.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOTD_API UStatsChangeEffectCalculation : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
    UStatsChangeEffectCalculation();
    virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

protected:
    FGameplayEffectAttributeCaptureDefinition StrengthCapture;
};
