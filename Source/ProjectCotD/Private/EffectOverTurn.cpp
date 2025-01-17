// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectOverTurn.h"

void UEffectOverTurn::Setup() const
{
	TurnRemaining = TurnApplied;
}


int32 UEffectOverTurn::DecreaseTurnRemaining()
{
	TurnRemaining -= 1;
	return TurnRemaining;
}