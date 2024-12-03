// Fill out your copyright notice in the Description page of Project Settings.

#include "COTDGameplayAbility.h"
#include "AbilitySystemComponent.h"

void UCOTDGameplayAbility::ApplyCustomGameplayEffectToTarget(UAbilitySystemComponent* TargetAbilitySystem, TSubclassOf<UGameplayEffect> EffectClass)
{
    if (!TargetAbilitySystem || !EffectClass) return;

    UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
    if (AbilitySystemComponent)
    {
        FGameplayEffectContextHandle GameplayEffectContextHandle = AbilitySystemComponent->MakeEffectContext();
        GameplayEffectContextHandle.AddSourceObject(this);
        GameplayEffectContextHandle.Get()->SetEffectCauser(GetAvatarActorFromActorInfo());

        FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(EffectClass, GetAbilityLevel(), GameplayEffectContextHandle);
        if (EffectSpecHandle.IsValid())
        {
            AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), TargetAbilitySystem);
        }
    }
}