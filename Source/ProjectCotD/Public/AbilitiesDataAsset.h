// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AbilitiesDataAsset.generated.h"

/**
 * 
 */


UCLASS()
class PROJECTCOTD_API UAbilitiesDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Data")
    FText Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Data")
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Data")
    UTexture2D* Icon;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Data")
    float Range;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Data")
    float BaseDamage;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Data")
    float SupplementDamage;
};
