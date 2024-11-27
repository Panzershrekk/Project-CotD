// Fill out your copyright notice in the Description page of Project Settings.

#include "COTDGameplayAbility.h"
#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystemComponent.h"
#include "ControllableEntity.h"
#include "DamageExecutionCalculation.h"
#include "ControllableEntityAttributeSet.h"
#include "GameFramework/Actor.h"

struct DamageCapture
{
    DECLARE_ATTRIBUTE_CAPTUREDEF(Health);
    DECLARE_ATTRIBUTE_CAPTUREDEF(MaxHealth);

    DamageCapture()
    {
        DEFINE_ATTRIBUTE_CAPTUREDEF(UControllableEntityAttributeSet, Health, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UControllableEntityAttributeSet, MaxHealth, Target, false);
    }
};

static DamageCapture& GetDamageCapture()
{
    static DamageCapture DamageCapture;
    return DamageCapture;
}

UDamageExecutionCalculation::UDamageExecutionCalculation()
{
    RelevantAttributesToCapture.Add(GetDamageCapture().HealthDef);
    RelevantAttributesToCapture.Add(GetDamageCapture().MaxHealthDef);

}

void UDamageExecutionCalculation::Execute_Implementation(
    const FGameplayEffectCustomExecutionParameters& ExecutionParams,
    FGameplayEffectCustomExecutionOutput& OutExecutionOutput
) const
{
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

    float Health = 0.0f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().HealthDef, EvaluationParameters, Health);
    
    float MaxHealth = 0.0f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().MaxHealthDef, EvaluationParameters, MaxHealth);

    //float HealthToAdd = -FMath::Clamp(MaxHealth - Health, 0.0f, 1.0f);
    float HealthToAdd = -1;

    OutExecutionOutput.AddOutputModifier(
        FGameplayModifierEvaluatedData(GetDamageCapture().HealthProperty, EGameplayModOp::Additive, HealthToAdd));
        /*float MinimumDamage = 0.f;
    float DamageVariation = 0.f;
    float Resistance = 0.f;

    const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

    if (const UObject* SourceObject = Spec.GetEffectContext().GetSourceObject())
    {
        if (const UCOTDGameplayAbility* AbilityData = Cast<UCOTDGameplayAbility>(SourceObject))
        {
            MinimumDamage = AbilityData->AbilitiesDataAsset->BaseDamage;
            DamageVariation = AbilityData->AbilitiesDataAsset->SupplementDamage;
        }
    }*/

    /*if (const UObject* TargetObject = Spec.GetEffectContext().GetTargetObject())
    {
        if (const AControllableEntity* TargetEntity = Cast<AControllableEntity>(TargetObject))
        {
            Resistance = 0;
        }
    }*/

    /*float RandomVariation = FMath::RandRange(0.f, DamageVariation);
    float TotalDamage = FMath::Max(0.f, MinimumDamage + RandomVariation - Resistance);*/
    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Some variable values: x: %f"), 5));

    /*OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(
        FGameplayAttribute(), EGameplayModOp::Additive, TotalDamage
    ));*/
}