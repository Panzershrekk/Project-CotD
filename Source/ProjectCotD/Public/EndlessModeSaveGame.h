// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EndlessRunState.h"
#include "GameFramework/SaveGame.h"
#include "EndlessModeSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOTD_API UEndlessModeSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FEndlessRunState RunState;
};
