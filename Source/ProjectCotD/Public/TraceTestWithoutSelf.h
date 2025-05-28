// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "TraceTestWithoutSelf.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOTD_API UTraceTestWithoutSelf : public UEnvQueryTest
{
    GENERATED_BODY()

public:
    UTraceTestWithoutSelf();

protected:
    virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;

public:
    UPROPERTY(EditDefaultsOnly, Category = Trace)
    TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Visibility;

    UPROPERTY(EditDefaultsOnly, Category = Trace)
    float ItemHeightOffset = 0.0f;

    UPROPERTY(EditDefaultsOnly, Category = Trace)
    float ContextHeightOffset = 0.0f;

    UPROPERTY(EditDefaultsOnly, Category = Trace, meta = (AllowAnyContext))
    TSubclassOf<UEnvQueryContext> TraceFromContext;
	
};
