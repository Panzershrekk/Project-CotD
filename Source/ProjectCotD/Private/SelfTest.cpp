// Fill out your copyright notice in the Description page of Project Settings.


#include "SelfTest.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Point.h"

USelfTest::USelfTest()
{
    ValidItemType = UEnvQueryItemType_Point::StaticClass();
}

void USelfTest::RunTest(FEnvQueryInstance& QueryInstance) const
{
    const AActor* QuerierActor = Cast<AActor>(QueryInstance.Owner.Get());
    if (!QuerierActor)
    {
        return;
    }

    FVector QuerierLocation = QuerierActor->GetActorLocation();
    QuerierLocation.Z = 0;

    for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
    {
        FVector ItemLocation = GetItemLocation(QueryInstance, It.GetIndex());
        ItemLocation.Z = 0;
        const float Distance = FVector::Dist(ItemLocation, QuerierLocation);
        const float Score = (Distance < Tolerance) ? 1.0f : 0.0f;

        It.SetScore(EEnvTestPurpose::Score, EEnvTestFilterType::Range, Score, 0.0f, 1.0f);
    }
}