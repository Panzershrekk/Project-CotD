// Fill out your copyright notice in the Description page of Project Settings.

#include "COTDGameplayAbility.h"
#include "GameplayEffect.h"

void UCOTDGameplayAbility::ApplyCustomGameplayEffectToTarget(UCOTDAbilitySystemComponent* TargetAbilitySystem, TSubclassOf<UGameplayEffect> EffectClass)
{
    if (!TargetAbilitySystem || !EffectClass) return;

    UCOTDAbilitySystemComponent* AbilitySystemComponent = Cast<UCOTDAbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo());
    if (AbilitySystemComponent)
    {
        FGameplayEffectContextHandle GameplayEffectContextHandle = AbilitySystemComponent->MakeEffectContext();
        GameplayEffectContextHandle.AddSourceObject(this);
        GameplayEffectContextHandle.Get()->SetEffectCauser(GetAvatarActorFromActorInfo());

        FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(EffectClass, GetAbilityLevel(), GameplayEffectContextHandle);
        if (EffectSpecHandle.IsValid())
        {
            //Check if it's an overturn effect
            if (EffectClass && EffectClass->IsChildOf(UEffectOverTurn::StaticClass()))
            {
                const UEffectOverTurn* EffectOverTurn = Cast<UEffectOverTurn>(EffectSpecHandle.Data->Def);
                if (EffectOverTurn)
                {
                    FGameplayTag TurnRemainingTag = FGameplayTag::RequestGameplayTag(FName("TurnRemaining"));
                    EffectSpecHandle.Data->SetSetByCallerMagnitude(TurnRemainingTag, 6.0f);
                    UE_LOG(LogTemp, Warning, TEXT("SetByCallerMagnitude TurnRemaining: %f, Address: %p"), EffectSpecHandle.Data->GetSetByCallerMagnitude(TurnRemainingTag, false), EffectOverTurn);
				}
                FActiveGameplayEffectHandle EffectHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), TargetAbilitySystem);
                if (EffectOverTurn)
                {
                    if (EffectOverTurn->bExecutePeriodicEffectOnApplication == true)
                    {
                        AbilitySystemComponent->TriggerPeriodicEffect(EffectHandle);
                    }
                }
            }
                //const FActiveGameplayEffect *AGE = AbilitySystemComponent->GetActiveGameplayEffect(AGEH);
            /*FActiveGameplayEffectsContainer& ActiveEffectsContainer = AGE;
            AbilitySystemComponent->ExecutePeriodicEffect(EffectSpecHandle);

                //ActiveGameplayEffects.ExecuteActiveEffectsFrom(Spec, PredictionKey);
                EffectClass->*/
        }
    }
}