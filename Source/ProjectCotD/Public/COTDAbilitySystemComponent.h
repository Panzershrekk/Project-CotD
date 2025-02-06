#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "COTDAbilitySystemComponent.generated.h"

class AAuraRadiusActor;
class UCOTDGameplayAbility;

/**
 * 
 */
UCLASS()
class PROJECTCOTD_API UCOTDAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditDefaultsOnly, Category = "Aura")
    TSubclassOf<AAuraRadiusActor> AuraActorClass;

    TMap<FActiveGameplayEffectHandle, TWeakObjectPtr<AAuraRadiusActor>> ActiveAuraEffects;

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

    UFUNCTION(BlueprintCallable, Category = "GAS")
    void ApplyCustomGameplayEffectToTarget(UCOTDGameplayAbility* GA, UCOTDAbilitySystemComponent* Target, TSubclassOf<UGameplayEffect> EffectClass, float EffectLevel);
    void OnEffectRemoved(const FActiveGameplayEffect& RemovedEffect);
};
