// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
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
    //Attributes
    UPROPERTY(BlueprintReadWrite)
    FEndlessRunState CurrentRunState;

    //Function
    UFUNCTION(BlueprintCallable)
    void InitRun();

	UFUNCTION(BlueprintCallable)
	void InitRunWithGivenSeed(int32 Seed);

    UFUNCTION(BlueprintCallable)
    TArray<FMapNode> GenerateRowAtDepth(int32 Depth);

    UFUNCTION(BlueprintCallable)
    void StartCombat(const FMapNode& Node);

    UFUNCTION(BlueprintCallable)
    void RestoreRun(const UEndlessModeSaveGame* SaveData)
    {
        CurrentRunState = SaveData->RunState;
    }

    UFUNCTION(BlueprintCallable)
    int32 GenerateRandomSeed()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int32> distrib(INT_MIN, INT_MAX);

        return distrib(gen);
    }
};
