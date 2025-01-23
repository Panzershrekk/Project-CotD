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
        //DEFINE_ATTRIBUTE_CAPTUREDEF(UControllableEntityAttributeSet, Intelligence, Source, true);
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
    UE_LOG(LogTemp, Warning, TEXT("Dynamic Stat change"));
    /* KindofTemplate*/
    /*UAbilitySystemComponent* TargetABSC = ExecutionParams.GetTargetAbilitySystemComponent();
    AActor* TargetActor = TargetABSC ? TargetABSC->GetAvatarActor() : nullptr;

    UAbilitySystemComponent* SourceABSC = ExecutionParams.GetSourceAbilitySystemComponent();
    AActor* SourceActor = SourceABSC ? SourceABSC->GetAvatarActor() : nullptr;

    const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
    const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
    const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

    FAggregatorEvaluateParameters EvaluationParameters;
    EvaluationParameters.SourceTags = SourceTags;
    EvaluationParameters.TargetTags = TargetTags;
    UE_LOG(LogTemp, Warning, TEXT("Applying stats change"));


    const UObject* SourceObject = Spec.GetEffectContext().GetSourceObject();
    float Strenght = 0.0f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetStatsCapture().StrenghtDef, EvaluationParameters, Strenght);      
    int32 Calaculated = 2;

	OutExecutionOutput.AddOutputModifier(
		  FGameplayModifierEvaluatedData(GetStatsCapture().StrenghtProperty, EGameplayModOp::Additive, Calaculated));
    */




    //
    /*float TargetStrenght = 0.0f;
    FAggregatorEvaluateParameters EvaluationParameters;

    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetStatsCapture().StrenghtDef, EvaluationParameters, TargetStrenght);

    //ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetStatsCapture().IntelligenceDef, EvaluationParameters, SourceIntelligence);

    float CalculatedStrenght = 2.0f;
    OutExecutionOutput.AddOutputModifier(
        FGameplayModifierEvaluatedData(GetStatsCapture().StrenghtProperty, EGameplayModOp::Additive, CalculatedStrenght));*/
        // Obtenez les composants AbilitySystem
    UAbilitySystemComponent* TargetABSC = ExecutionParams.GetTargetAbilitySystemComponent();
    UAbilitySystemComponent* SourceABSC = ExecutionParams.GetSourceAbilitySystemComponent();

    // Capture des attributs
    FAggregatorEvaluateParameters EvaluationParameters;
    const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

    // Récupération de l'intelligence de la source
    float SourceIntelligence = 0.0f;
    /*ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
        FGameplayEffectAttributeCaptureDefinition(
            UControllableEntityAttributeSet::GetIntelligenceAttribute(),
            EGameplayEffectAttributeCaptureSource::Source,
            true),
        EvaluationParameters,
        SourceIntelligence);*/

    // Calcul de la force à ajouter
    float CalculatedStrength = 2.0f + SourceIntelligence;

    // Définition de la magnitude pour le modificateur
    OutExecutionOutput.AddOutputModifier(
        FGameplayModifierEvaluatedData(GetStatsCapture().StrenghtProperty, EGameplayModOp::Additive, CalculatedStrength));

}