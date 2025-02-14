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
	OrderOfPlayList.Empty();
	UE_LOG(LogTemp, Warning, TEXT("Starting combat"));
	for (AControllableEntity* Entity : AllControllableEntities)
	{
		AddEntityByInitiative(Entity);
	}
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

void UBattleManager::AddEntityByInitiative(AControllableEntity* Entity)
{
	if (!Entity) return;
	int32 InsertIndex = 0;
	Entity->RollInitiative();
	for (; InsertIndex < OrderOfPlayList.Num(); ++InsertIndex)
	{
		if (Entity->GetInitiative() > OrderOfPlayList[InsertIndex]->GetInitiative())
		{
			break;
		}
	}
	OrderOfPlayList.Insert(Entity, InsertIndex);
}

void UBattleManager::RemoveEntityFromPlay(AControllableEntity* Entity)
{
	if (!Entity) return;
	OrderOfPlayList.Remove(Entity);
}

void UBattleManager::CheckForBattleEnd()
{
}