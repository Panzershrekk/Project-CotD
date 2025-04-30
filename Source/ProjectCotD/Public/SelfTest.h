// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "SelfTest.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOTD_API USelfTest : public UEnvQueryTest
{
	GENERATED_BODY()
public:
	USelfTest();
	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
	UPROPERTY(EditDefaultsOnly, Category = "Test")
	float Tolerance = 1.0f;
};
