// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "COTDGameInstance.h"
#include "EndlessModeSaveGame.h"
#include "random"
#include "COTDEndlessGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOTD_API ACOTDEndlessGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:

    UPROPERTY(BlueprintReadOnly, Category = "Manager")
    UCOTDGameInstance* GI;

    UPROPERTY(BlueprintReadOnly, Category = "Manager")
    USaveManager* SaveManager;

    /*UPROPERTY(BlueprintReadOnly, Category = "Affixes")
    TArray<TSubclassOf<FEndlessRunBuff>> PossiblesAffixesForEnemy;*/
    //Function

    //CALL THAT IN BP BEFORE ANYTHING
    UFUNCTION(BlueprintCallable)
    void InitClass(UCOTDGameInstance* GameInstance);

    UFUNCTION(BlueprintCallable)
    void InitRun();

	UFUNCTION(BlueprintCallable)
	void InitRunWithGivenSeed(int32 Seed);

    UFUNCTION(BlueprintCallable)
    void ProcessCombatResult();

    UFUNCTION(BlueprintCallable)
    TArray<FMapNode> GenerateRowAtDepth(int32 Depth);

    UFUNCTION(BlueprintCallable)
    void AddEnemyBuffOnNode(FMapNode& MapNode, const FEndlessRunBuff& MapEnemyBuff);

    UFUNCTION(BlueprintCallable)
    int32 GenerateRandomSeed()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int32> distrib(INT_MIN, INT_MAX);

        return distrib(gen);
    }
};
