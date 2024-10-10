// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BattleManager.generated.h"

UCLASS()
class PROJECTCOTD_API ABattleManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABattleManager();

	bool isbattleStarted;
	int currentTurn;

	//---> PSeudo code
	//List<CurentPlayable> all entities
	//List<OrdererPlayeble> initiative

	UFUNCTION(BlueprintCallable, Category = "BattleFlow")
	void StartCombat();

	void DefineNextPlayableEntity();
	void CheckForBattleEnd();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
