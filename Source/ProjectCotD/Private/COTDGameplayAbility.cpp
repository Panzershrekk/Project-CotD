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
            FActiveGameplayEffectHandle EffectHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), TargetAbilitySystem);
            //Check if it's an overturn effect
            if (EffectClass && EffectClass->IsChildOf(UEffectOverTurn::StaticClass()))
            {
                const UEffectOverTurn* EffectOverTurn = Cast<UEffectOverTurn>(EffectSpecHandle.Data->Def);
                if (EffectOverTurn)
                {
                    UE_LOG(LogTemp, Warning, TEXT("Applying remain"));
                    EffectSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("TurnRemaining")), 6);
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