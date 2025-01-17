// Fill out your copyright notice in the Description page of Project Settings.


#include "COTDAbilitySystemComponent.h"

void UCOTDAbilitySystemComponent::DecreaseOverTurnEffectTurnRemaining(const UEffectOverTurn* Effect, FActiveGameplayEffectHandle& EffectHandle)
{
	if (Effect && EffectHandle.IsValid())
	{
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
