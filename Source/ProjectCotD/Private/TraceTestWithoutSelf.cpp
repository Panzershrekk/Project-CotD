// Fill out your copyright notice in the Description page of Project Settings.


#include "TraceTestWithoutSelf.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Point.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"

UTraceTestWithoutSelf::UTraceTestWithoutSelf()
{
    ValidItemType = UEnvQueryItemType_Point::StaticClass();
    //bWorkOnFloatValues = true;
}

void UTraceTestWithoutSelf::RunTest(FEnvQueryInstance& QueryInstance) const
{
    TArray<FVector> ContextLocations;

    UClass* ContextClass = TraceFromContext ? *TraceFromContext : UEnvQueryContext::StaticClass();
    QueryInstance.PrepareContext(ContextClass, ContextLocations);

    if (ContextLocations.Num() == 0)
    {
        return;
    }

    const AActor* QuerierActor = Cast<AActor>(QueryInstance.Owner.Get());

    for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
    {
        FVector ItemLocation = GetItemLocation(QueryInstance, It.GetIndex()) + FVector(0, 0, ItemHeightOffset);

        float BestScore = 0.0f;

        for (const FVector& RawContextLocation : ContextLocations)
        {
            FVector ContextLocation = RawContextLocation + FVector(0, 0, ContextHeightOffset);

            FHitResult Hit;
            FCollisionQueryParams Params;
            Params.bTraceComplex = false;

            if (QuerierActor)
            {
                Params.AddIgnoredActor(QuerierActor);
            }

            bool bHit = QueryInstance.World->LineTraceSingleByChannel(
                Hit,
                ContextLocation,
                ItemLocation,
                TraceChannel,
                Params
            );

            const float ThisScore = bHit ? 0.0f : 1.0f;
            BestScore = FMath::Max(BestScore, ThisScore);

            //Optional to test
            if (ThisScore >= 1.0f)
                break;
        }

        It.SetScore(EEnvTestPurpose::Score, EEnvTestFilterType::Range, BestScore, 0.0f, 1.0f);
    }
}