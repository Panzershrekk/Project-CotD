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

    float BaseDamage = 0.f;
    float SupplementVariation = 0.f;

    if (SourceActor)
    {
        //AControllableEntity* SourceEntity = SourceActor->FindComponentByClass<AControllableEntity>();

        //if (SourceEntity)
        //{
            BaseDamage = 4;//SourceAbility->AbilitiesDataAsset->BaseDamage;
            SupplementVariation = 4;//SourceAbility->AbilitiesDataAsset->SupplementDamage;
        //}
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

    //float HealthToAdd = -FMath::Clamp(MaxHealth - Health, 0.0f, 1.0f);
    int32 HealthToAdd = BaseDamage + FMath::RandRange(0, static_cast<int32>(FMath::FloorToInt(SupplementVariation)));

  
    if (SourceActor->GetWorld())
    {
        UCOTDGameInstance* GI = Cast<UCOTDGameInstance>(SourceActor->GetWorld()->GetGameInstance());
        if (TargetActor && GI && GI->UIManager)
        {
            GI->UIManager->ShowHealthChangeFloating(TargetActor->GetActorLocation(), FString::FromInt(HealthToAdd));
        }
    }
    else
    {
        if (GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Enorme proutorrr!"));
    }
    OutExecutionOutput.AddOutputModifier(
        FGameplayModifierEvaluatedData(GetDamageCapture().HealthProperty, EGameplayModOp::Additive, HealthToAdd));
}