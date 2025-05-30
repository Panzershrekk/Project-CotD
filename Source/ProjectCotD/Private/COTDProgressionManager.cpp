// Fill out your copyright notice in the Description page of Project Settings.


#include "COTDProgressionManager.h"

void UCOTDProgressionManager::Initialize(UCOTDGameInstance* Instance)
{
	COTDGameInstance = Instance;
}

float UCOTDProgressionManager::GetRequiredEXPToLevelUP(float Level) const
{
	return 100.f * Level + FMath::Pow(Level, 2) * 10.f;
}
