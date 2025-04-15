// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TargetSelectorActor.h"
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

UENUM(BlueprintType)
enum class EAreaSelectionType : uint8
{
    //The area will be created where the cursor is
    FromCursor UMETA(DisplayName = "From Cursor"),
    //The area will be created from caster and follow the mouse (exemple a direct line)
    FromCaster UMETA(DisplayName = "From Caster"),
};

USTRUCT(BlueprintType)
struct FAreaSelector
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AreaSelector")
    TSubclassOf<ATargetSelectorActor> AreaType;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AreaSelector")
    FVector AreaSelectorSize;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AreaSelector")
    EAreaSelectionType AreaSelectionType;
};

