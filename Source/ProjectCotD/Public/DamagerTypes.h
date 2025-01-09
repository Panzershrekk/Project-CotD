// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "DamagerTypes.generated.h"

// Enum pour les types principaux de dégâts
UENUM(BlueprintType)
enum class EDamagerType : uint8
{
    Physical UMETA(DisplayName = "Physical"),
    Magical UMETA(DisplayName = "Magical"),
};

// Enum pour les sous-types de dégâts
UENUM(BlueprintType)
enum class ESubDamagerType : uint8
{
    None UMETA(DisplayName = "None"),
    Blunt UMETA(DisplayName = "Blunt"),
    Slashing UMETA(DisplayName = "Slashing"),
    Piercing UMETA(DisplayName = "Piercing"),
    Fire UMETA(DisplayName = "Fire"),
    Frost UMETA(DisplayName = "Frost"),
    Wind UMETA(DisplayName = "Wind"),
    Shadow UMETA(DisplayName = "Shadow"),
};

USTRUCT(BlueprintType)
struct FDamagerInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    EDamagerType DamageType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    ESubDamagerType SubDamageType;

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