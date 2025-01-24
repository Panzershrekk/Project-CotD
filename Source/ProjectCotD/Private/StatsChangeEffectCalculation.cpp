// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsChangeEffectCalculation.h"
#include "COTDGameplayAbility.h"
#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystemComponent.h"
#include "ControllableEntity.h"
#include "ControllableEntityAttributeSet.h"
#include "COTDGameInstance.h"

struct StatsCapture
{
    DECLARE_ATTRIBUTE_CAPTUREDEF(Strenght);

    StatsCapture()
    {
        DEFINE_ATTRIBUTE_CAPTUREDEF(UControllableEntityAttributeSet, Strenght, Target, false);
        //DEFINE_ATTRIBUTE_CAPTUREDEF(UControllableEntityAttributeSet, Intelligence, Source, true);
    }
};

static StatsCapture& GetStatsCapture()
{
    static StatsCapture DamageCapture;
    return DamageCapture;
}

UStatsChangeEffectCalculation::UStatsChangeEffectCalculation()
{
    RelevantAttributesToCapture.Add(GetStatsCapture().StrenghtDef);
}

float UStatsChangeEffectCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
    float CapturedStrengthValue = 0.0f;

    FAggregatorEvaluateParameters EvaluationParameters;
    EvaluationParameters.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
    EvaluationParameters.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

    const FGameplayEffectAttributeCaptureSpec* CaptureSpec = Spec.CapturedRelevantAttributes.FindCaptureSpecByDefinition(StrengthCapture, true);
    if (CaptureSpec && CaptureSpec->AttemptCalculateAttributeMagnitude(EvaluationParameters, CapturedStrengthValue))
    {
        const float BonusMultiplier = 2.0f;
        return CapturedStrengthValue * BonusMultiplier;
    }
    return 0.0f;
}