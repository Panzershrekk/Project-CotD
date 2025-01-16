// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicStatsChangeExecution.h"
#include "COTDGameplayAbility.h"
#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystemComponent.h"
#include "ControllableEntity.h"
#include "ControllableEntityAttributeSet.h"
#include "COTDGameInstance.h"

/*
*
*/
struct StatsCapture
{
    DECLARE_ATTRIBUTE_CAPTUREDEF(Strenght);

    StatsCapture()
    {
        DEFINE_ATTRIBUTE_CAPTUREDEF(UControllableEntityAttributeSet, Strenght, Target, false);
    }
};

static StatsCapture& GetStatsCapture()
{
    static StatsCapture DamageCapture;
    return DamageCapture;
}

UDynamicStatsChangeExecution::UDynamicStatsChangeExecution()
{
    RelevantAttributesToCapture.Add(GetStatsCapture().StrenghtDef);
}

void UDynamicStatsChangeExecution::Execute_Implementation(
    const FGameplayEffectCustomExecutionParameters& ExecutionParams,
    FGameplayEffectCustomExecutionOutput& OutExecutionOutput
) const
{
    /* KindofTemplate*/
    UAbilitySystemComponent* TargetABSC = ExecutionParams.GetTargetAbilitySystemComponent();
    AActor* TargetActor = TargetABSC ? TargetABSC->GetAvatarActor() : nullptr;

    UAbilitySystemComponent* SourceABSC = ExecutionParams.GetSourceAbilitySystemComponent();
    AActor* SourceActor = SourceABSC ? SourceABSC->GetAvatarActor() : nullptr;

    const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
    const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
    const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

    FAggregatorEvaluateParameters EvaluationParameters;
    EvaluationParameters.SourceTags = SourceTags;
    EvaluationParameters.TargetTags = TargetTags;
    /* KindofTemplate*/
    UE_LOG(LogTemp, Warning, TEXT("Applying stats change"));

    //This will allow to get attribute from other entity
    /*
    if (ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
        FGameplayEffectAttributeCaptureDefinition(
            UAttributeSetBase::GetIntelligenceAttribute(), EGameplayEffectAttributeCaptureSource::Source, true),
        FAggregatorEvaluateParameters(),
        IntelligenceValue))
    {
        BaseValue = 10.0f; // Ex. valeur de base
    }*/


    const UObject* SourceObject = Spec.GetEffectContext().GetSourceObject();
    float Strenght = 0.0f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetStatsCapture().StrenghtDef, EvaluationParameters, Strenght);      
    int32 Calaculated = 2; 

	OutExecutionOutput.AddOutputModifier(
		  FGameplayModifierEvaluatedData(GetStatsCapture().StrenghtProperty, EGameplayModOp::Additive, Calaculated));

}