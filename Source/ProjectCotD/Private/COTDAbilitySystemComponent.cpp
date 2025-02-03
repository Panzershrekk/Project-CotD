// Fill out your copyright notice in the Description page of Project Settings.


#include "COTDAbilitySystemComponent.h"

void UCOTDAbilitySystemComponent::DecreaseOverTurnEffectTurnRemaining(FActiveGameplayEffectHandle& EffectHandle)
{
    if (EffectHandle.IsValid())
    {
        const FActiveGameplayEffect* ActiveEffect = GetActiveGameplayEffect(EffectHandle);
        if (ActiveEffect)
        {
            FGameplayTag TurnRemainingTag = FGameplayTag::RequestGameplayTag(FName("TurnRemaining"));

            const FGameplayEffectSpec& Spec = ActiveEffect->Spec;
            float CurrentTurnRemaining = Spec.GetSetByCallerMagnitude(TurnRemainingTag, false);

            UE_LOG(LogTemp, Warning, TEXT("Turn remaining: %f"), CurrentTurnRemaining);

            CurrentTurnRemaining -= 1.0f;

            if (CurrentTurnRemaining <= 0.0f && CurrentTurnRemaining != -1)
            {
                RemoveActiveGameplayEffect(EffectHandle);
            }
            else
            {
                const FActiveGameplayEffect* MutableActiveEffect = GetActiveGameplayEffect(EffectHandle);
                FGameplayEffectSpec& MutableSpec = const_cast<FGameplayEffectSpec&>(MutableActiveEffect->Spec);
                MutableSpec.SetSetByCallerMagnitude(TurnRemainingTag, CurrentTurnRemaining);
                CurrentTurnRemaining = Spec.GetSetByCallerMagnitude(TurnRemainingTag, false);

                /*if (MutableActiveEffect)
                {
                    MutableActiveEffect->Spec.SetSetByCallerMagnitude(TurnRemainingTag, CurrentTurnRemaining);
                }*/
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("No active effect found for handle."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid EffectHandle."));
    }
}

//TBD
void UCOTDAbilitySystemComponent::ApplyCustomGameplayEffectToTarget(UCOTDAbilitySystemComponent* TargetAbilitySystem, UCOTDGameplayAbility* Ability, TSubclassOf<UGameplayEffect> EffectClass)
{
    if (!TargetAbilitySystem || !EffectClass) return;


        FGameplayEffectContextHandle GameplayEffectContextHandle = this->MakeEffectContext();
        GameplayEffectContextHandle.AddSourceObject(this);
        GameplayEffectContextHandle.Get()->SetEffectCauser(Ability->GetAvatarActorFromActorInfo());

        FGameplayEffectSpecHandle EffectSpecHandle = this->MakeOutgoingSpec(EffectClass, Ability->GetAbilityLevel(), GameplayEffectContextHandle);
        if (EffectSpecHandle.IsValid())
        {
            const UEffectOverTurn* EffectOverTurn = Cast<UEffectOverTurn>(EffectSpecHandle.Data->Def);;
            //Check if it's an overturn effect
            if (EffectClass && EffectOverTurn)
            {
                FGameplayTag TurnRemainingTag = FGameplayTag::RequestGameplayTag(FName("TurnRemaining"));
                EffectSpecHandle.Data->SetSetByCallerMagnitude(TurnRemainingTag, EffectOverTurn->TurnApplied);
                UE_LOG(LogTemp, Warning, TEXT("SetByCallerMagnitude TurnRemaining: %f, Address: %p"), EffectSpecHandle.Data->GetSetByCallerMagnitude(TurnRemainingTag, false), EffectOverTurn);
            }
            UE_LOG(LogTemp, Warning, TEXT("Applying stuff"));
            FActiveGameplayEffectHandle EffectHandle = this->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), TargetAbilitySystem);
            if (EffectOverTurn)
            {
                if (EffectOverTurn->bTriggerCalculationClassOnApply == true)
                {
                    TargetAbilitySystem->TriggerPeriodicEffect(EffectHandle);
                }
            }
        }
}