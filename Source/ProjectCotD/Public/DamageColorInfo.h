// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamagerTypes.h"
#include "DamageColorInfo.generated.h"

USTRUCT(BlueprintType)
struct FDamageColorInfo : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    FGameplayTag SubDamageType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    FLinearColor DamageColor;

    FDamageColorInfo() : SubDamageType(), DamageColor(FLinearColor::White) {}
};