// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "EffectOverTurn.h"
#include "COTDAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOTD_API UCOTDAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:

    //Custom function to trigger calculation function on periodic effect
    void TriggerPeriodicEffect(FActiveGameplayEffectHandle Handle)
    {
        //ActiveGameplayEffects.ExecutePeriodicGameplayEffect(Handle);
    }

    const FActiveGameplayEffectsContainer& GetActiveGameplayEffectsContainer() const
    {
        return ActiveGameplayEffects;
    }

    UFUNCTION(BlueprintCallable, Category = "GAS")
    void DecreaseOverTurnEffectTurnRemaining(FActiveGameplayEffectHandle& EffectHandle);

    UFUNCTION(BlueprintCallable, Category = "GAS")

    float GetSetByCallerMagnitudeFromEffect(FActiveGameplayEffectHandle EffectHandle, FGameplayTag CallerTag) const
    {
        if (const FActiveGameplayEffect* ActiveEffect = GetActiveGameplayEffect(EffectHandle))
        {
            return ActiveEffect->Spec.GetSetByCallerMagnitude(CallerTag, false);
        }

        return -1.0f;
    }
};
