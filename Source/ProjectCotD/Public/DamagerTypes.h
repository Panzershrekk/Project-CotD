// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "DamagerTypes.generated.h"


USTRUCT(BlueprintType)
struct FDamagerInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    FGameplayTag DamageTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    FGameplayTag SubDamageTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    int32 BaseDamage;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    int32 SupplementDamage;
};

USTRUCT(BlueprintType)
struct FDamagerDisplayInfo
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    int32 DamageDone;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color")
    FLinearColor DisplayColor;
};