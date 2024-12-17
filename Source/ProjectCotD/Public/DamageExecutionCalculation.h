// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "DamageExecutionCalculation.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FInformations
{
    GENERATED_BODY()

    UPROPERTY()
    AActor* TargetActor = nullptr;

    UPROPERTY()
    AActor* SourceActor = nullptr;

    UPROPERTY()
    class UCOTDGameInstance* GI = nullptr;

    FInformations() {}
    FInformations(AActor* Target, AActor* Source, class UCOTDGameInstance* G) {
        TargetActor = Target;
        SourceActor = Source;
        GI = G;
    }

};

UCLASS()
class PROJECTCOTD_API UDamageExecutionCalculation : public UGameplayEffectExecutionCalculation
{
    GENERATED_BODY()
    
public:
    FInformations mutable Info;
    UDamageExecutionCalculation();

    virtual void Execute_Implementation(
        const FGameplayEffectCustomExecutionParameters& ExecutionParams,
        FGameplayEffectCustomExecutionOutput& OutExecutionOutput
    ) const override;
	
    void OnHealthChanged(const FOnAttributeChangeData& Data) const;
};
