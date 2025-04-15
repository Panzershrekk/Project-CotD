// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "COTDProjectile.h"
#include "DamagerTypes.h"
#include "COTDUtils.h"
#include "Engine/DataAsset.h"
#include "AbilitiesDataAsset.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ETargetingType : uint8
{
    SingleTarget UMETA(DisplayName = "Single Target"),
    MultiTarget UMETA(DisplayName = "Multi Target"),
    AreaOfEffect UMETA(DisplayName = "Area of Effect"),
    Self UMETA(DisplayName = "Self"),
    Global UMETA(DisplayName = "Global")
};

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
    TArray<FDamagerInfo> DamagersInfos;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Data")
    ETargetingType TargetingType;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Data")
    bool IsAreaOfEffect;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Data")
    FAreaSelector AreaSelector;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Data")
    bool RequireATarget;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Data")
    bool RequireLineOfSight;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Data")
    bool IsProjectile;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Data")
    int32 MartialPointCost;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Data")
    int32 MagicPointCost;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Data", meta = (EditCondition = "IsProjectile"))
    TSubclassOf<ACOTDProjectile> ProjectileActor;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Data", meta = (EditCondition = "IsProjectile"))
    float ProjectileArc;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Data", meta = (EditCondition = "IsProjectile"))
    float ProjectileSpeed;
};