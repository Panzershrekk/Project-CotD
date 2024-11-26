// Fill out your copyright notice in the Description page of Project Settings.

#include "COTDGameplayAbility.h"
#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystemComponent.h"
#include "ControllableEntity.h"
#include "DamageExecutionCalculation.h"
#include "GameFramework/Actor.h"

UDamageExecutionCalculation::UDamageExecutionCalculation()
{
    // Vous pouvez ajouter ici des "Capture Definitions" pour collecter les stats nécessaires.
}

void UDamageExecutionCalculation::Execute_Implementation(
    const FGameplayEffectCustomExecutionParameters& ExecutionParams,
    FGameplayEffectCustomExecutionOutput& OutExecutionOutput
) const
{
    float MinimumDamage = 0.f;
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
    }

    /*if (const UObject* TargetObject = Spec.GetEffectContext().GetTargetObject())
    {
        if (const AControllableEntity* TargetEntity = Cast<AControllableEntity>(TargetObject))
        {
            Resistance = 0;
        }
    }*/

    float RandomVariation = FMath::RandRange(0.f, DamageVariation);
    float TotalDamage = FMath::Max(0.f, MinimumDamage + RandomVariation - Resistance);

    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(
        FGameplayAttribute(), EGameplayModOp::Additive, TotalDamage
    ));
}