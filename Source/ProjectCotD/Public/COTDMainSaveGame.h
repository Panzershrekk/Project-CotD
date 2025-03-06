// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "COTDMainSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOTD_API UCOTDMainSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
    UCOTDMainSaveGame();
    UPROPERTY(BlueprintReadWrite, Category = "SaveData")
    int32 TotalXP;

    UPROPERTY(BlueprintReadWrite, Category = "SaveData")
    int32 Treasure;
};
