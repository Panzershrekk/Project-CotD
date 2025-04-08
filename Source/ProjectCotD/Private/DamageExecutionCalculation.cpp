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
    DECLARE_ATTRIBUTE_CAPTUREDEF(DamageMultiplier);

    DamageCapture()
    {
        DEFINE_ATTRIBUTE_CAPTUREDEF(UControllableEntityAttributeSet, Health, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UControllableEntityAttributeSet, MaxHealth, Target, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UControllableEntityAttributeSet, DamageMultiplier, Source, false);
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
    RelevantAttributesToCapture.Add(GetDamageCapture().DamageMultiplierDef);

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



    const UObject* SourceObject = Spec.GetEffectContext().GetSourceObject();
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

    float DamageMultiplier = 1.0f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().DamageMultiplierDef, EvaluationParameters, DamageMultiplier);

    if (SourceObject)
    {
        const UCOTDGameplayAbility* SourceGameplayAbility = Cast<UCOTDGameplayAbility>(SourceObject);
        TQueue<FDamagerDisplayInfo> DamageQueueDisplayer;
        UCOTDGameInstance* GI = nullptr;
        if (SourceActor && SourceActor->GetWorld())
        {
            GI = Cast<UCOTDGameInstance>(SourceActor->GetWorld()->GetGameInstance());
            if (GI == nullptr)
            {
                UE_LOG(LogTemp, Warning, TEXT("Instance is null"));
            }
        }
        for (FDamagerInfo DamagerInfo : SourceGameplayAbility->AbilitiesDataAsset->DamagersInfos)
        {
            int32 BaseDamage = DamagerInfo.BaseDamage;
            int32 SupplementVariation = DamagerInfo.SupplementDamage;
            UE_LOG(LogTemp, Warning, TEXT("Damage multiplier is %f"), DamageMultiplier);

            int32 Calaculated = (BaseDamage + FMath::RandRange(0, SupplementVariation)) * DamageMultiplier;

            FDamagerDisplayInfo Displayer;
            Displayer.DisplayColor = FLinearColor::White;
            Displayer.DamageDone = Calaculated;
            if (GI && GI->DamageColorManager)
            {
                Displayer.DisplayColor = GI->DamageColorManager->GetColorForDamageType(DamagerInfo.SubDamageTag);
            }
            DamageQueueDisplayer.Enqueue(Displayer);
            OutExecutionOutput.AddOutputModifier(
                FGameplayModifierEvaluatedData(GetDamageCapture().HealthProperty, EGameplayModOp::Additive, -Calaculated));
            TargetABSC->GetGameplayAttributeValueChangeDelegate(GetDamageCapture().HealthProperty).RemoveAll(this);
            TargetABSC->GetGameplayAttributeValueChangeDelegate(GetDamageCapture().HealthProperty).AddUObject(
                this, &UDamageExecutionCalculation::OnHealthChanged);

            Info = FDamageOriginInformations(TargetActor, SourceActor, GI);
        }
        if (TargetActor && GI && GI->UIManager)
        {
            GI->UIManager->ShowHealthChangeFloating(TargetActor->GetActorLocation(), DamageQueueDisplayer);
            //GI->UIManager->UpdateHealth(TargetActor);
        }
    }
}

void UDamageExecutionCalculation::OnHealthChanged(const FOnAttributeChangeData& Data) const
{
    if (Info.GI && Info.GI->UIManager && Info.TargetActor)
    {
        Info.GI->BattleManager->ApplyDamageToEntityAndUpdateUI(Info.TargetActor);
    }
}