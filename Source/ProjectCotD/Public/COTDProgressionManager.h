// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ControllableEntityAttributeSet.h"
#include "COTDUtils.h"
#include "COTDProgressionManager.generated.h"

class UCOTDGameInstance;

/**
 * 
 */
UCLASS()
class PROJECTCOTD_API UCOTDProgressionManager : public UObject
{
	GENERATED_BODY()
	
public:
	void Initialize(UCOTDGameInstance* Instance);

	UPROPERTY(BlueprintReadOnly, Category = "Progression")
	UCOTDGameInstance* COTDGameInstance;

	UFUNCTION(BlueprintCallable, Category = "EXP")
	void GrantExpToHero(FHeroSaveData& Hero, float Amount);

	UFUNCTION(BlueprintCallable, Category = "EXP")
	bool GrantExperienceToHeroById(FPrimaryAssetId HeroId, float Amount);
	UFUNCTION(BlueprintCallable, Category = "EXP")
	float GetRequiredEXPToLevelUP(float Level) const;

	UFUNCTION(BlueprintCallable, Category = "ProgressStats")
	void GiveMainStatsToHero(FHeroSaveData& Hero, COTDStatsType StatsType, float Amount);
	UFUNCTION(BlueprintCallable, Category = "ProgressStats")
	bool GiveMainStatsToHeroByID(FPrimaryAssetId HeroId, COTDStatsType StatsType, float Amount);

	UFUNCTION(BlueprintCallable, Category = "ProgressStats")
	void RemoveMainStatsFromHero(FHeroSaveData& Hero, COTDStatsType StatsType, float Amount);
	UFUNCTION(BlueprintCallable, Category = "ProgressStats")
	bool RemoveMainStatsFromHeroByID(FPrimaryAssetId HeroId, COTDStatsType StatsType, float Amount);

	UFUNCTION(BlueprintCallable, Category = "ProgressStats")
	float GetMainStatsFromHeroID(FPrimaryAssetId HeroId, COTDStatsType StatsType);
};
