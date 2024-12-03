// Fill out your copyright notice in the Description page of Project Settings.

#include "DamageExecutionCalculation.h"
#include "COTDGameplayAbility.h"
#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystemComponent.h"
#include "ControllableEntity.h"
#include "ControllableEntityAttributeSet.h"
#include "COTDGameInstance.h"
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

    int32 BaseDamage = 0;
    int32 SupplementVariation = 0;

    /*if (const UObject* SourceObject = Spec.GetEffectContext().GetSourceObject())
    {
        if (const UCOTDGameplayAbility* AbilityData = Cast<UCOTDGameplayAbility>(SourceObject))
        {
            if (GEngine)
                GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("World delta for current frame equals %f"), AbilityData->AbilitiesDataAsset->BaseDamage));
            MinimumDamage = AbilityData->AbilitiesDataAsset->BaseDamage;
            DamageVariation = AbilityData->AbilitiesDataAsset->SupplementDamage;
        }
    }*/
    const UObject* SourceObject = Spec.GetEffectContext().GetSourceObject();
    if (SourceObject)
    {
        const UCOTDGameplayAbility* SourceGameplayAbility = Cast<UCOTDGameplayAbility>(SourceObject);
        if (SourceGameplayAbility)
        {
            BaseDamage = SourceGameplayAbility->AbilitiesDataAsset->BaseDamage;
            SupplementVariation = SourceGameplayAbility->AbilitiesDataAsset->SupplementDamage;
        }

    }
    /*if (TargetActor)
    {
        AControllableEntity* TargetEntity = SourceActor->FindComponentByClass<AControllableEntity>();
        if (TargetEntity)
        {
            //TBD
        }
    }*/


    float Health = 0.0f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().HealthDef, EvaluationParameters, Health);
    
    float MaxHealth = 0.0f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().MaxHealthDef, EvaluationParameters, MaxHealth);

    int32 Calaculated = BaseDamage + FMath::RandRange(0, SupplementVariation);

    if (SourceActor && SourceActor->GetWorld())
    {
        UCOTDGameInstance* GI = Cast<UCOTDGameInstance>(SourceActor->GetWorld()->GetGameInstance());
        if (TargetActor && GI && GI->UIManager)
        {
            GI->UIManager->ShowHealthChangeFloating(TargetActor->GetActorLocation(), FString::FromInt(Calaculated));
        }
    }
    OutExecutionOutput.AddOutputModifier(
        FGameplayModifierEvaluatedData(GetDamageCapture().HealthProperty, EGameplayModOp::Additive, Calaculated));
}