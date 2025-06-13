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

bool UCOTDProgressionManager::GrantExperienceToHeroById(FPrimaryAssetId HeroId, float Amount)
{
    FHeroSaveData* FoundHero = COTDGameInstance->SaveManager->GetCurrentSaveGame()->UnlockedHeroes.FindByPredicate([&](const FHeroSaveData& Data)
        {
            return Data.EntityDataId == HeroId;
        });

    if (!FoundHero)
    {
        UE_LOG(LogTemp, Warning, TEXT("Hero %s not found in unlocked heroes."), *HeroId.ToString());
        return false;
    }

    GrantExpToHero(*FoundHero, Amount);
    return true;
}

float UCOTDProgressionManager::GetRequiredEXPToLevelUP(float Level) const
{
	return 100.f * Level + FMath::Pow(Level, 2) * 10.f;
}

void UCOTDProgressionManager::GiveMainStatsToHero(FHeroSaveData& Hero, COTDStatsType StatsType, float Amount)
{
    float DefAmount = Amount;
    if (Amount >= Hero.UnassignedStatPoints)
    {
        DefAmount = Hero.UnassignedStatPoints;
    }
    Hero.UnassignedStatPoints -= DefAmount;
    switch (StatsType)
    {
    case COTDStatsType::Strength:
        Hero.Strength += DefAmount;
        break;
    case COTDStatsType::Intelligence:
        Hero.Intelligence += DefAmount;
        break;
    case COTDStatsType::Stamina:
        Hero.Stamina += DefAmount;
        break;
    case COTDStatsType::Wisdom:
        Hero.Wisdom += DefAmount;
        break;
    case COTDStatsType::Luck:
        Hero.Luck += DefAmount;
        break;
    case COTDStatsType::Cunning:
        Hero.Cunning += DefAmount;
        break;
    default:
        UE_LOG(LogTemp, Warning, TEXT("AddStatToHero: Invalid StatType"));
        break;
    }

    COTDGameInstance->SaveManager->SaveGame();
}

bool UCOTDProgressionManager::GiveMainStatsToHeroByID(FPrimaryAssetId HeroId, COTDStatsType StatsType, float Amount)
{
    FHeroSaveData* FoundHero = COTDGameInstance->SaveManager->GetCurrentSaveGame()->UnlockedHeroes.FindByPredicate([&](const FHeroSaveData& Data)
        {
            return Data.EntityDataId == HeroId;
        });

    if (!FoundHero)
    {
        UE_LOG(LogTemp, Warning, TEXT("Hero %s not found in unlocked heroes."), *HeroId.ToString());
        return false;
    }

    GiveMainStatsToHero(*FoundHero, StatsType, Amount);
    return true;
}

void UCOTDProgressionManager::RemoveMainStatsFromHero(FHeroSaveData& Hero, COTDStatsType StatsType, float Amount)
{
    float DefAmount = Amount;
    switch (StatsType)
    {
    case COTDStatsType::Strength:
        if (Hero.Strength <= Amount)
        {
            DefAmount = Hero.Strength;
        }
        Hero.Strength -= DefAmount;
        break;
    case COTDStatsType::Intelligence:
        if (Hero.Intelligence <= Amount)
        {
            DefAmount = Hero.Intelligence;
        }
        Hero.Intelligence -= DefAmount;
        break;
    case COTDStatsType::Stamina:
        if (Hero.Stamina <= Amount)
        {
            DefAmount = Hero.Stamina;
        }
        Hero.Stamina -= DefAmount;
        break;
    case COTDStatsType::Wisdom:
        if (Hero.Wisdom <= Amount)
        {
            DefAmount = Hero.Wisdom;
        }
        Hero.Wisdom -= DefAmount;
        break;
    case COTDStatsType::Luck:
        if (Hero.Luck <= Amount)
        {
            DefAmount = Hero.Luck;
        }
        Hero.Luck -= DefAmount;
        break;
    case COTDStatsType::Cunning:
        if (Hero.Cunning <= Amount)
        {
            DefAmount = Hero.Cunning;
        }
        Hero.Cunning -= DefAmount;
        break;
    default:
        UE_LOG(LogTemp, Warning, TEXT("AddStatToHero: Invalid StatType"));
        break;
    }
    Hero.UnassignedStatPoints += DefAmount;
    COTDGameInstance->SaveManager->SaveGame();
}

bool UCOTDProgressionManager::RemoveMainStatsFromHeroByID(FPrimaryAssetId HeroId, COTDStatsType StatsType, float Amount)
{
    FHeroSaveData* FoundHero = COTDGameInstance->SaveManager->GetCurrentSaveGame()->UnlockedHeroes.FindByPredicate([&](const FHeroSaveData& Data)
        {
            return Data.EntityDataId == HeroId;
        });

    if (!FoundHero)
    {
        UE_LOG(LogTemp, Warning, TEXT("Hero %s not found in unlocked heroes."), *HeroId.ToString());
        return false;
    }

    RemoveMainStatsFromHero(*FoundHero, StatsType, Amount);
    return true;
}

float UCOTDProgressionManager::GetMainStatsFromHeroID(FPrimaryAssetId HeroId, COTDStatsType StatsType)
{
    FHeroSaveData* FoundHero = COTDGameInstance->SaveManager->GetCurrentSaveGame()->UnlockedHeroes.FindByPredicate([&](const FHeroSaveData& Data)
        {
            return Data.EntityDataId == HeroId;
        });

    if (!FoundHero)
    {
        UE_LOG(LogTemp, Warning, TEXT("Hero %s not found in unlocked heroes."), *HeroId.ToString());
        return -1.0f;
    }
    FHeroSaveData Hero = *FoundHero;
    switch (StatsType)
    {
    case COTDStatsType::Strength:
        return Hero.Strength;
    case COTDStatsType::Intelligence:
        return Hero.Intelligence;
    case COTDStatsType::Stamina:
        return Hero.Stamina;
    case COTDStatsType::Wisdom:
        return Hero.Wisdom;
    case COTDStatsType::Luck:
        return Hero.Luck;
    case COTDStatsType::Cunning:
        return Hero.Cunning;
    default:
        UE_LOG(LogTemp, Warning, TEXT("AddStatToHero: Invalid StatType"));
        return -1.0f;
    }
}
