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


void UBattleManager::StartCombat()
{
	//Roll initative
	IsbattleStarted = true;
	CurrentTurn = 0;
	OrderOfPlayList = AllControllableEntities;
	OrderOfPlayList.Sort([](const AControllableEntity& A, const AControllableEntity& B)
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
	for (int32 Index = 0; Index < OrderOfPlayList.Num(); ++Index)
	{
		if (OrderOfPlayList[Index] == CurrentPlaying)
		{
			if (Index + 1 < OrderOfPlayList.Num())
			{
				return OrderOfPlayList[Index + 1];
			}
			else
			{
				return OrderOfPlayList[0];
			}
		}
	}
	return nullptr;
}

void UBattleManager::CheckForBattleEnd()
{
}