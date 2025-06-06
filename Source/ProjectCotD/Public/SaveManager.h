// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "COTDMainSaveGame.h"
#include "EndlessRunState.h"
#include "EntityStatsDataAsset.h"
#include "Engine/AssetManager.h"
#include "SaveManager.generated.h"

class UCOTDGameInstance;

UCLASS(Blueprintable, BlueprintType)
class PROJECTCOTD_API USaveManager : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Instance")
	UCOTDGameInstance* COTDGameInstance;

	USaveManager();
	void Initialize(UCOTDGameInstance* Instance);

	UFUNCTION(BlueprintCallable, Category = "SaveSystem")
	void SaveGame();

	UFUNCTION(BlueprintCallable, Category = "SaveSystem")
	void LoadGame();

	UFUNCTION(BlueprintPure, Category = "SaveSystem")
	UCOTDMainSaveGame* GetCurrentSaveGame() const { return CurrentSaveGame; }

	/*********** PARTY HANDLING **********/

	UFUNCTION(BlueprintCallable, Category = "Party")
	void UnlockHero(UEntityStatsDataAsset* HeroDataAsset);

	UFUNCTION(BlueprintCallable, Category = "Party")
	void RemoveAndAddHeroToParty(FHeroSaveData& ToRemoveHero, FHeroSaveData& ToAddHero);

	UFUNCTION(BlueprintCallable, Category = "Party")
	void AddHeroToParty(FHeroSaveData& ToAddHero);

	/*********** ENDLESS RUN ************/

	UFUNCTION(BlueprintCallable, Category = "EndlessMode")
	void SaveEndlessRunState(const FEndlessRunState& State);

	UFUNCTION(BlueprintCallable, Category = "EndlessMode")
	bool LoadEndlessRunState(FEndlessRunState& OutState);

	UFUNCTION(BlueprintCallable, Category = "EndlessMode")
	void CreateNewRunWithSeed(int32 Seed);

	UFUNCTION(BlueprintCallable, Category = "EndlessMode")
	void ClearEndlessRunState();

	UFUNCTION(BlueprintCallable, Category = "EndlessMode")
	void AddBuffToEndlessRun(TSubclassOf<UGameplayEffect> BuffEffect, int32 Count = 1, bool bUnique = false);

	UFUNCTION(BlueprintCallable, Category = "EndlessMode")
	void AddCompleteBuffToEndlessRun(FEndlessRunBuff Buff);
private:
	UPROPERTY()
	UCOTDMainSaveGame* CurrentSaveGame;
	const FString SaveSlotName = TEXT("COTDMainSaveFile"); //No touchy
};
