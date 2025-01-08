// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamagerTypes.h"
#include "DamageColorInfo.generated.h"

USTRUCT(BlueprintType)
struct FDamageColorInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    ESubDamagerType SubDamageType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    FLinearColor DamageColor;

    FDamageColorInfo() : SubDamageType(ESubDamagerType::None), DamageColor(FLinearColor::White) {}
};