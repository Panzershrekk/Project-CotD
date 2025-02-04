// Fill out your copyright notice in the Description page of Project Settings.

#include "COTDGameplayAbility.h"
#include "GameplayEffect.h"


void UCOTDGameplayAbility::ApplyCustomGameplayEffectToTarget(UCOTDAbilitySystemComponent* TargetAbilitySystem, TSubclassOf<UGameplayEffect> EffectClass)
{
    if (!TargetAbilitySystem || !EffectClass) return;

    UCOTDAbilitySystemComponent* AbilitySystemComponent = Cast<UCOTDAbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo());
    if (AbilitySystemComponent)
    {
        AActor* EffectCauser = GetAvatarActorFromActorInfo();
        FGameplayEffectContextHandle GameplayEffectContextHandle = AbilitySystemComponent->MakeEffectContext();
        GameplayEffectContextHandle.AddSourceObject(this);
        GameplayEffectContextHandle.Get()->SetEffectCauser(EffectCauser);

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
            const UGameplayEffectAura* EffectAura = Cast<UGameplayEffectAura>(EffectSpecHandle.Data->Def);;
            if (AuraActorClass && EffectAura && EffectCauser)
            {
                FActorSpawnParameters SpawnParams;
                SpawnParams.Owner = EffectCauser;
                SpawnParams.Instigator = EffectCauser->GetInstigator();

                AAuraRadiusActor* AuraInstance = EffectCauser->GetWorld()->SpawnActor<AAuraRadiusActor>(AuraActorClass, EffectCauser->GetActorLocation(), FRotator::ZeroRotator, SpawnParams);
                if (AuraInstance)
                {
                    AuraInstance->Initialize(EffectCauser, EffectAura);
                    SpawnedActorsForEffect.Add(AuraInstance);
                }
            }
            UE_LOG(LogTemp, Warning, TEXT("Applying stuff"));
            FActiveGameplayEffectHandle EffectHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), TargetAbilitySystem);
            if (EffectOverTurn)
            {
                if (EffectOverTurn->bTriggerCalculationClassOnApply == true)
                {
                    TargetAbilitySystem->TriggerPeriodicEffect(EffectHandle);
                }
            }
            AbilitySystemComponent->OnAnyGameplayEffectRemovedDelegate().AddUObject(this, &UCOTDGameplayAbility::OnEffectRemoved);
        }
    }
}

void UCOTDGameplayAbility::OnEffectRemoved(const FActiveGameplayEffect& EffectRemoved)
{
    for (int i = 0; SpawnedActorsForEffect.Num(); i++)
    {
        if (SpawnedActorsForEffect[i])
        {
            SpawnedActorsForEffect[i]->Destroy();
            SpawnedActorsForEffect[i] = nullptr;
        }
    }
    UE_LOG(LogTemp, Warning, TEXT("Actors spawned destroyed"));
    SpawnedActorsForEffect.Empty();
}