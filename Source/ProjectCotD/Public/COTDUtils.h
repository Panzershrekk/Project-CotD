// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "COTDUtils.generated.h"

/**
 *
 */

USTRUCT(BlueprintType)
struct FDamageOriginInformations
{
    GENERATED_BODY()

    UPROPERTY()
    AActor* TargetActor = nullptr;

    UPROPERTY()
    AActor* SourceActor = nullptr;

    UPROPERTY()
    class UCOTDGameInstance* GI = nullptr;

    FDamageOriginInformations() {}
    FDamageOriginInformations(AActor* Target, AActor* Source, class UCOTDGameInstance* G) {
        TargetActor = Target;
        SourceActor = Source;
        GI = G;
    }

};
