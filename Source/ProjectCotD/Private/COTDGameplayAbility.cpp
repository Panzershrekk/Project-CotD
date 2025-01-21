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
            const UEffectOverTurn* EffectOverTurn = Cast<UEffectOverTurn>(EffectSpecHandle.Data->Def);;
            //Check if it's an overturn effect
            if (EffectClass && EffectOverTurn)
            {
                FGameplayTag TurnRemainingTag = FGameplayTag::RequestGameplayTag(FName("TurnRemaining"));
                EffectSpecHandle.Data->SetSetByCallerMagnitude(TurnRemainingTag, EffectOverTurn->TurnApplied);
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
    }
}