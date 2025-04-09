// Fill out your copyright notice in the Description page of Project Settings.


#include "COTDAbilitySystemComponent.h"
#include "EffectOverTurn.h"
#include "AuraRadiusActor.h"
#include "GameplayEffectAura.h"
#include "COTDGameplayAbility.h"

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

            if (CurrentTurnRemaining != -1)
            {
                CurrentTurnRemaining -= 1.0f;
            }

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

void UCOTDAbilitySystemComponent::ApplyCustomGameplayEffectToTarget(UCOTDGameplayAbility* GA, UCOTDAbilitySystemComponent* TargetAbilitySystem, TSubclassOf<UGameplayEffect> EffectClass, float EffectLevel)
{
    
    //AActor* EffectCauser = GetAvatarActorFromActorInfo();
    if (!TargetAbilitySystem || !EffectClass) return;

    AActor* EffectCauser = GA->GetAvatarActorFromActorInfo();
    FGameplayEffectContextHandle GameplayEffectContextHandle = MakeEffectContext();
    GameplayEffectContextHandle.AddSourceObject(GA);
    GameplayEffectContextHandle.Get()->SetEffectCauser(EffectCauser);

    FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingSpec(EffectClass, EffectLevel, GameplayEffectContextHandle);
    if (EffectSpecHandle.IsValid())
    {
        const UEffectOverTurn* EffectOverTurn = Cast<UEffectOverTurn>(EffectSpecHandle.Data->Def);
        //Check if it's an overturn effect
        if (EffectClass && EffectOverTurn)
        {
            FGameplayTag TurnRemainingTag = FGameplayTag::RequestGameplayTag(FName("TurnRemaining"));
            EffectSpecHandle.Data->SetSetByCallerMagnitude(TurnRemainingTag, EffectOverTurn->TurnApplied);
            UE_LOG(LogTemp, Warning, TEXT("SetByCallerMagnitude TurnRemaining: %f, Address: %p"), EffectSpecHandle.Data->GetSetByCallerMagnitude(TurnRemainingTag, false), EffectOverTurn);
        }
        const UGameplayEffectAura* EffectAura = Cast<UGameplayEffectAura>(EffectSpecHandle.Data->Def);
        AAuraRadiusActor* AuraInstance = nullptr;
        if (AuraActorClass && EffectAura && EffectCauser)
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = EffectCauser;
            SpawnParams.Instigator = EffectCauser->GetInstigator();

            AuraInstance = EffectCauser->GetWorld()->SpawnActor<AAuraRadiusActor>(AuraActorClass, EffectCauser->GetActorLocation(), FRotator::ZeroRotator, SpawnParams);
            if (AuraInstance)
            {
                AuraInstance->Initialize(EffectCauser, EffectAura, GA);
                /*Referencer l'actor de l'aura quelque part*/
                //ActiveAuraEffects.Add(EffectHandle, AuraInstance);
            }
        }
        UE_LOG(LogTemp, Warning, TEXT("Binding OnEffectRemoved delegate"));
        //TargetAbilitySystem->OnAnyGameplayEffectRemovedDelegate().AddUObject(this, &UCOTDGameplayAbility::OnEffectRemoved);
        UE_LOG(LogTemp, Warning, TEXT("Applying stuff"));
        FActiveGameplayEffectHandle EffectHandle = ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), TargetAbilitySystem);
        TargetAbilitySystem->OnAnyGameplayEffectRemovedDelegate().AddUObject(this, &UCOTDAbilitySystemComponent::OnEffectRemoved);
        if (EffectAura && EffectHandle.IsValid())
        {
            ActiveAuraEffects.Add(EffectHandle, AuraInstance);
        }
        if (EffectOverTurn && EffectOverTurn->bTriggerCalculationClassOnApply)
        {
            TargetAbilitySystem->TriggerPeriodicEffect(EffectHandle);
        }
    }
    
}

void UCOTDAbilitySystemComponent::OnEffectRemoved(const FActiveGameplayEffect& RemovedEffect)
{
    FActiveGameplayEffectHandle EffectHandle = RemovedEffect.Handle;
    if (ActiveAuraEffects.Contains(EffectHandle))
    {
        if (AAuraRadiusActor* AuraInstance = ActiveAuraEffects[EffectHandle].Get())
        {
            AuraInstance->Destroy();
        }
        ActiveAuraEffects.Remove(EffectHandle);
    }
}
