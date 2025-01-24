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
