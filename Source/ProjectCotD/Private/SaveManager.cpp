// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveManager.h"
#include "Kismet/GameplayStatics.h"

USaveManager::USaveManager()
{
}


void USaveManager::Initialize(UCOTDGameInstance* Instance)
{
    COTDGameInstance = Instance;
    UE_LOG(LogTemp, Warning, TEXT("Savemanager initilialize"));
    LoadGame();
}

void USaveManager::SaveGame()
{
    if (!CurrentSaveGame)
    {
        UE_LOG(LogTemp, Warning, TEXT("No save file detected, cannot save"));
        return;
    }

    UGameplayStatics::SaveGameToSlot(CurrentSaveGame, SaveSlotName, 0);
    UE_LOG(LogTemp, Warning, TEXT("Saving successful"));
}

void USaveManager::LoadGame()
{
    if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0))
    {
        CurrentSaveGame = Cast<UCOTDMainSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
        if (CurrentSaveGame)
        {
            UE_LOG(LogTemp, Warning, TEXT("Loading sucess"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No save file found, creating new save file."));
        CurrentSaveGame = Cast<UCOTDMainSaveGame>(UGameplayStatics::CreateSaveGameObject(UCOTDMainSaveGame::StaticClass()));
        SaveGame();
    }
}