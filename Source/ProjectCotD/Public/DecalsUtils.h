// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Components/DecalComponent.h"
#include "DecalsUtils.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOTD_API UDecalsUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Decal Size", Keywords = "Set Decal Size"), Category = "Decals")
	static void SetDecalSize(UDecalComponent* Decal, FVector Size) {
		Decal->DecalSize = Size;
		return;
	}
};
