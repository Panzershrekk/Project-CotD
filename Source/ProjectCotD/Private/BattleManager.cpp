// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleManager.h"

// Sets default values
UBattleManager::UBattleManager()
{
}

void UBattleManager::Initialize(UCOTDGameInstance* Instance)
{
	COTDGameInstance = Instance;
}


void UBattleManager::StartCombat(TArray<AControllableEntity*> controllableEntities)
{
	//Roll initative
	isbattleStarted = true;
	currentTurn = 0;
	allControllableEntities = controllableEntities;
	orderOfPlayList = controllableEntities;
	orderOfPlayList.Sort([](const AControllableEntity& A, const AControllableEntity& B)
		{
			return A.GetInitiative() < B.GetInitiative();
		});
}

AControllableEntity* UBattleManager::DefineNextPlayableEntity(AControllableEntity* CurrentPlaying)
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

void UBattleManager::CheckForBattleEnd()
{
}