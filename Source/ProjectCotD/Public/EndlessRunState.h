// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "COTDGameplayAbility.h"
#include "EndlessRunState.generated.h"

USTRUCT(BlueprintType)
struct PROJECTCOTD_API FEndlessRunBuff
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UGameplayEffect> GameplayEffectClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 StackCount = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bUnique = false;
};

USTRUCT(BlueprintType)
struct PROJECTCOTD_API FEndlessHeroState
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
    int32 EndlessCurrency;
    UPROPERTY(BlueprintReadOnly)
    int32 Seed;

    UPROPERTY(BlueprintReadWrite)
    TArray<FEndlessRunBuff> ActiveEndlessRunBuffs;
    UPROPERTY(BlueprintReadWrite)
    bool bRunInProgress = false;
};

USTRUCT(BlueprintType)
struct PROJECTCOTD_API FMapNode
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    int32 Depth;

    /*UPROPERTY(BlueprintReadOnly)
    FName NodeType;*/


    /*UPROPERTY(BlueprintReadOnly)
    TMap<FName, float> MapModifiers;*/

    // Identifiant unique pour la navigation ou sauvegarde
    UPROPERTY(BlueprintReadOnly)
    FGuid NodeID;
};





