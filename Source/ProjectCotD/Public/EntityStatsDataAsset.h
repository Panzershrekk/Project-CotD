// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "COTDGameplayAbility.h"
#include "Engine/DataAsset.h"
#include "EntityStatsDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOTD_API UEntityStatsDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Spells")
	TArray<UCOTDGameplayAbility*> GetAbilitiesDataAssets() const;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FText Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style")
	UStaticMesh* Model;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style")
	USkeletalMesh* SkeletonMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style")
	UTexture2D* UIImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style")
	UMaterial* MaterialTest;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	TSubclassOf<UAnimInstance> AnimClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	UDataTable* EntityNumericalStats;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spells")
	TArray<TSubclassOf<UCOTDGameplayAbility>> EntitySpells;
};

USTRUCT(BlueprintType)
struct FSpawnWithTeamInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	UEntityStatsDataAsset* EntityStatDataAsset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	int32 Team;
};