// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleManager.h"

// Sets default values
ABattleManager::ABattleManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABattleManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABattleManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABattleManager::StartCombat(TArray<AControllableEntity*> controllableEntities)
{
	//Roll initative
	isbattleStarted = true;
	currentTurn = 0;
	allControllableEntities = controllableEntities;
	orderOfPlayList = controllableEntities;
	orderOfPlayList.Sort([](const AControllableEntity& A, const AControllableEntity& B)
		{
			return A.GetInitiative() > B.GetInitiative();
		});
}

AControllableEntity* ABattleManager::DefineNextPlayableEntity(AControllableEntity* CurrentPlaying)
{

	if (!CurrentPlaying)
	{
		return nullptr;
	}
	for (int32 Index = 0; Index < orderOfPlayList.Num(); ++Index)
	{
		if (orderOfPlayList[Index] == CurrentPlaying)
		{
			if (Index + 1 < orderOfPlayList.Num())
			{
				return orderOfPlayList[Index + 1];
			}
			else
			{
				return orderOfPlayList[0];
			}
		}
	}
	return nullptr;
}

void ABattleManager::CheckForBattleEnd()
{
}