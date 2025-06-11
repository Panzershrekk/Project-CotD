// Fill out your copyright notice in the Description page of Project Settings.


#include "COTDProgressionManager.h"
#include "COTDGameInstance.h"

void UCOTDProgressionManager::Initialize(UCOTDGameInstance* Instance)
{
	COTDGameInstance = Instance;
}

void UCOTDProgressionManager::GrantExpToHero(FHeroSaveData& Hero, float Amount)
{
	int32 CurrentLevel = Hero.Level;

	Hero.Experience += Amount;
	while (Hero.Experience >= GetRequiredEXPToLevelUP(Hero.Level))
	{
		Hero.Experience -= GetRequiredEXPToLevelUP(Hero.Level);
		Hero.Level++;
		Hero.UnassignedStatPoints += 5; //TODO Put a config file for that

		UE_LOG(LogTemp, Log, TEXT("Hero %s leveled up to level %d!"), *Hero.EntityDataId.ToString(), Hero.Level);
	}
	COTDGameInstance->SaveManager->SaveGame();
}

float UCOTDProgressionManager::GetRequiredEXPToLevelUP(float Level) const
{
	return 100.f * Level + FMath::Pow(Level, 2) * 10.f;
}
