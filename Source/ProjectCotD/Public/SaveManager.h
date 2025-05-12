// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "COTDMainSaveGame.h"
#include "EndlessRunState.h"
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

	/*********** ENDLESS RUN ************/

	UFUNCTION(BlueprintCallable, Category = "EndlessMode")
	void SaveEndlessRunState(const FEndlessRunState& State);

	UFUNCTION(BlueprintCallable, Category = "EndlessMode")
	bool LoadEndlessRunState(FEndlessRunState& OutState);

	UFUNCTION(BlueprintCallable, Category = "EndlessMode")
	void ClearEndlessRunState();

private:
	UPROPERTY()
	UCOTDMainSaveGame* CurrentSaveGame;
	const FString SaveSlotName = TEXT("COTDMainSaveFile"); //No touchy
};
