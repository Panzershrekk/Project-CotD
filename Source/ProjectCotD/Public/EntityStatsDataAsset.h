// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FText Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Initiative;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float InitiativeVariation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float BaseMaxHitPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float BaseMaxMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float BaseStrenght;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float BaseIntelligence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float BaseAgility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	UStaticMesh* Model;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	USkeletalMesh* SkeletonMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	UTexture2D* UIImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	UMaterial* MaterialTest;

};
