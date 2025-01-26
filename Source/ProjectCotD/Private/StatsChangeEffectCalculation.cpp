// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsChangeEffectCalculation.h"
#include "COTDGameplayAbility.h"
#include "GameplayEffect.h"
#include "ControllableEntityAttributeSet.h"
#include "COTDGameInstance.h"

UStatsChangeEffectCalculation::UStatsChangeEffectCalculation()
{
    StrengthDef = FGameplayEffectAttributeCaptureDefinition(
        UControllableEntityAttributeSet::GetStrengthAttribute(), 
        EGameplayEffectAttributeCaptureSource::Source,          
        true                                                    
    );
    RelevantAttributesToCapture.Add(StrengthDef);
}

float UStatsChangeEffectCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
    FAggregatorEvaluateParameters EvaluationParameters;
    EvaluationParameters.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
    EvaluationParameters.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
    float Strength = 0.0f;
    GetCapturedAttributeMagnitude(StrengthDef, Spec, EvaluationParameters, Strength);
    Strength = FMath::Max<float>(Strength, 0.f);
    float FinalStrength = 2 + Strength;
    UE_LOG(LogTemp, Warning, TEXT("Stats up fail! %f"), Strength);
    return FinalStrength;
}