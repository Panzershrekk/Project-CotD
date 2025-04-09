// Fill out your copyright notice in the Description page of Project Settings.
#include "DOTEffectExecutionCalculation.h"
#include "COTDGameplayAbility.h"
#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystemComponent.h"
#include "ControllableEntity.h"
#include "ControllableEntityAttributeSet.h"
#include "COTDGameInstance.h"
#include "GameplayEffectDamageOverTurn.h"

/*
* 
*/
struct DotCapture
{
    DECLARE_ATTRIBUTE_CAPTUREDEF(Health);
    DECLARE_ATTRIBUTE_CAPTUREDEF(MaxHealth);

    DotCapture()
    {
        DEFINE_ATTRIBUTE_CAPTUREDEF(UControllableEntityAttributeSet, Health, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UControllableEntityAttributeSet, MaxHealth, Target, false);
    }
};

static DotCapture& GetDotCapture()
{
    static DotCapture DamageCapture;
    return DamageCapture;
}

UDOTEffectExecutionCalculation::UDOTEffectExecutionCalculation()
{
    RelevantAttributesToCapture.Add(GetDotCapture().HealthDef);
    RelevantAttributesToCapture.Add(GetDotCapture().MaxHealthDef);
}

void UDOTEffectExecutionCalculation::Execute_Implementation(
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

    const UObject* SourceObject = Spec.GetEffectContext().GetSourceObject();

    float Health = 0.0f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDotCapture().HealthDef, EvaluationParameters, Health);

    float MaxHealth = 0.0f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDotCapture().MaxHealthDef, EvaluationParameters, MaxHealth);

    const UGameplayEffectDamageOverTurn* DOTEffect = Cast<UGameplayEffectDamageOverTurn>(Spec.Def);
    UCOTDGameInstance* GI = nullptr;

    if (SourceActor && SourceActor->GetWorld())
    {
        GI = Cast<UCOTDGameInstance>(SourceActor->GetWorld()->GetGameInstance());
    }
    if (DOTEffect)
    {
        int32 BaseDamage = 1;
        int32 Calaculated = BaseDamage;

        FDamagerDisplayInfo Displayer;
        Displayer.DisplayColor = FLinearColor::White;
        Displayer.DamageDone = Calaculated;
        if (GI && GI->DamageManager)
        {
            Displayer.DisplayColor = GI->DamageManager->GetColorForDamageType(DOTEffect->DamagerInfo.SubDamageTag);
        }
        OutExecutionOutput.AddOutputModifier(
            FGameplayModifierEvaluatedData(GetDotCapture().HealthProperty, EGameplayModOp::Additive, -Calaculated));
        TargetABSC->GetGameplayAttributeValueChangeDelegate(GetDotCapture().HealthProperty).RemoveAll(this);
        TargetABSC->GetGameplayAttributeValueChangeDelegate(GetDotCapture().HealthProperty).AddUObject(
            this, &UDOTEffectExecutionCalculation::OnHealthChanged);

        Info = FDamageOriginInformations(TargetActor, SourceActor, GI);
        if (TargetActor && GI && GI->UIManager)
        {
             GI->UIManager->ShowHealthChangeFloating(TargetActor->GetActorLocation(), Displayer);
        }
    }
}

void UDOTEffectExecutionCalculation::OnHealthChanged(const FOnAttributeChangeData& Data) const
{
    if (Info.GI && Info.GI->UIManager && Info.TargetActor)
    {
        Info.GI->BattleManager->ApplyDamageToEntityAndUpdateUI(Info.TargetActor);
    }
}