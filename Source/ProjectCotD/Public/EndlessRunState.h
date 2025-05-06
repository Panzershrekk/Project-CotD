// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "EndlessRunState.generated.h"

USTRUCT(BlueprintType)
struct PROJECTCOTD_API FHeroState
{
    GENERATED_BODY()

    //Here put the data related to the hero party

    /*UPROPERTY()
    FName HeroID;
    UPROPERTY()
    float CurrentHP;
    UPROPERTY()
    TArray<FName> ActiveBuffs;*/
};

USTRUCT(BlueprintType)
struct PROJECTCOTD_API FEndlessRunState
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    int32 Depth;
    UPROPERTY(BlueprintReadOnly)
    int32 Gold;
    UPROPERTY(BlueprintReadOnly)
    int32 Seed;
};







