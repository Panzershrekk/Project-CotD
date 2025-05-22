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
    UE_LOG(LogTemp, Warning, TEXT("Saving whole game successful"));
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

/************ END LESS *************/
UFUNCTION(BlueprintCallable, Category = "EndlessMode")
void USaveManager::SaveEndlessRunState(const FEndlessRunState& State)
{
    if (!CurrentSaveGame) return;

    CurrentSaveGame->EndlessRunState = State;
    UE_LOG(LogTemp, Warning, TEXT("Saving endlessRun state"));
    SaveGame();
}

UFUNCTION(BlueprintCallable, Category = "EndlessMode")
bool USaveManager::LoadEndlessRunState(FEndlessRunState& OutState)
{
    if (!CurrentSaveGame) return false;

    OutState = CurrentSaveGame->EndlessRunState;
    return OutState.bRunInProgress;
}

void USaveManager::CreateNewRunWithSeed(int32 Seed)
{
    FEndlessRunState NewRun = FEndlessRunState();
    NewRun.Seed = Seed;
    NewRun.bRunInProgress = true;
    SaveEndlessRunState(NewRun);
}

void USaveManager::ClearEndlessRunState()
{
    if (!CurrentSaveGame)
    {
        UE_LOG(LogTemp, Warning, TEXT("ClearEndlessRunState: CurrentSaveGame is null."));
        return;
    }
    CurrentSaveGame->EndlessRunState = FEndlessRunState();
    SaveGame();

    UE_LOG(LogTemp, Log, TEXT("Endless run state cleared and save game updated."));
}

void USaveManager::AddBuffToEndlessRun(TSubclassOf<UGameplayEffect> BuffEffect, int32 Count, bool bUnique)
{
    for (FEndlessRunBuff& Buff : CurrentSaveGame->EndlessRunState.ActiveEndlessRunBuffs)
    {
        if (Buff.GameplayEffectClass == BuffEffect)
        {
            if (!Buff.bUnique)
            {
                Buff.StackCount += Count;
                SaveGame();
            }
            return;
        }
    }

    FEndlessRunBuff NewBuff;
    NewBuff.GameplayEffectClass = BuffEffect;
    NewBuff.StackCount = Count;
    NewBuff.bUnique = bUnique;
    CurrentSaveGame->EndlessRunState.ActiveEndlessRunBuffs.Add(NewBuff);
    SaveGame();
}

void USaveManager::AddCompleteBuffToEndlessRun(FEndlessRunBuff Buff)
{
    if (!Buff.GameplayEffectClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("Buff is invalid: GameplayEffectClass is null"));
        return;
    }
    TSubclassOf<UGameplayEffect> BuffEffect = Buff.GameplayEffectClass;
    int32 Count = Buff.StackCount;
    bool bUnique = Buff.bUnique;

    for (FEndlessRunBuff& Buff : CurrentSaveGame->EndlessRunState.ActiveEndlessRunBuffs)
    {
        if (Buff.GameplayEffectClass == BuffEffect)
        {
            if (!Buff.bUnique)
            {
                Buff.StackCount += Count;
                SaveGame();
            }
            return;
        }
    }

    FEndlessRunBuff NewBuff;
    NewBuff.GameplayEffectClass = BuffEffect;
    NewBuff.StackCount = Count;
    NewBuff.bUnique = bUnique;
    CurrentSaveGame->EndlessRunState.ActiveEndlessRunBuffs.Add(NewBuff);
    SaveGame();
}
