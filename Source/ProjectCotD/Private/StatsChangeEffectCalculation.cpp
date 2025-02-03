// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsChangeEffectCalculation.h"
#include "ControllableEntityAttributeSet.h"


/***** ! CAUTION ! *****/
// Don't capture the attribute you are modifying, or it will be called 2 times
/**********************/

UStatsChangeEffectCalculation::UStatsChangeEffectCalculation()
{

    /*StrengthDef.AttributeToCapture = UControllableEntityAttributeSet::GetStrengthAttribute();
    StrengthDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
    StrengthDef.bSnapshot = false;
    RelevantAttributesToCapture.Add(StrengthDef);*/
}

float UStatsChangeEffectCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
    const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
    const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

    FAggregatorEvaluateParameters EvaluationParameters;
    EvaluationParameters.TargetTags = TargetTags;
    EvaluationParameters.SourceTags = SourceTags;

    float Strength = 0.0f;
    //GetCapturedAttributeMagnitude(StrengthDef, Spec, EvaluationParameters, Strength);
    Strength = FMath::Max<float>(Strength, 0.f);
    float FinalStrength = 2 /* + Strength*/;
    UE_LOG(LogTemp, Warning, TEXT("Changing stats !"), Strength);
    return FinalStrength;
}