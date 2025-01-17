// Fill out your copyright notice in the Description page of Project Settings.


#include "COTDAbilitySystemComponent.h"

void UCOTDAbilitySystemComponent::DecreaseOverTurnEffectTurnRemaining(FGameplayEffectSpec Spec, FActiveGameplayEffectHandle& EffectHandle)
{
	//EffectSpecHandle.Data->GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("TurnRemaining")), EffectOverTurn->TurnApplied);

	if (EffectHandle.IsValid())
	{
		FGameplayTag TurnRemainingTag = FGameplayTag::RequestGameplayTag(FName("TurnRemaining"));
		float CurrentTurnRemaining = Spec.GetSetByCallerMagnitude(TurnRemainingTag, false);
		UE_LOG(LogTemp, Warning, TEXT("Turn remainig %f, effect or effect handle is undefined"), CurrentTurnRemaining);

		CurrentTurnRemaining -= 1;
		if (CurrentTurnRemaining <= 0)
		{
			this->RemoveActiveGameplayEffect(EffectHandle);
		}
		Spec.SetSetByCallerMagnitude(TurnRemainingTag, CurrentTurnRemaining);
		/*int32 TurnRemaining = Effect->DecreaseTurnRemaining();
		if (TurnRemaining <= 0)
		{
			this->RemoveActiveGameplayEffect(EffectHandle);
		}*/
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Error in %s, effect or effect handle is undefined"), *GetClass()->GetName());
	}
}
