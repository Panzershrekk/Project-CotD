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

/********* PARTY **********/

void USaveManager::UnlockHero(UEntityStatsDataAsset* HeroDataAsset)
{
    if (!HeroDataAsset)
    {
        UE_LOG(LogTemp, Warning, TEXT("UnlockHero called with null HeroDataAsset!"));
        return;
    }

    UAssetManager& AssetManager = UAssetManager::Get();
    FPrimaryAssetId HeroAssetId = HeroDataAsset->GetPrimaryAssetId();

    bool bAlreadyUnlocked = CurrentSaveGame->UnlockedHeroes.ContainsByPredicate([&](const FHeroSaveData& Data)
        {
            return Data.EntityDataId == HeroAssetId;
        });

    if (bAlreadyUnlocked)
    {
        UE_LOG(LogTemp, Log, TEXT("Hero %s is already unlocked"), *HeroAssetId.ToString());
        return;
    }

    FHeroSaveData NewProgressionData;
    NewProgressionData.EntityDataId = HeroAssetId;

    /**TODO Default init, need to change that later **/
    NewProgressionData.Level = 1;
    NewProgressionData.UnassignedStatPoints = 0;

    NewProgressionData.Strength = 10.f;
    NewProgressionData.Intelligence = 10.f;
    NewProgressionData.Stamina = 10.f;
    NewProgressionData.Wisdom = 10.f;

    CurrentSaveGame->UnlockedHeroes.Add(NewProgressionData);
    SaveGame();
    UE_LOG(LogTemp, Log, TEXT("Hero %s unlocked!"), *HeroAssetId.ToString());
}

void USaveManager::RemoveAndAddHeroToParty(FHeroSaveData& ToRemoveHero, FHeroSaveData& ToAddHero)
{
    /*bool bInParty = CurrentSaveGame->ActiveHeroes.ContainsByPredicate([&](const FHeroSaveData& Data)
        {
            return Data.EntityDataId.ToString().Equals(ToRemoveHero.EntityDataId.ToString());
        });
    if (!bInParty)
    {
        UE_LOG(LogTemp, Log, TEXT("Hero %s is not in active Party"), *ToRemoveHero.EntityDataId.ToString());
    }
    else
    {
        CurrentSaveGame->ActiveHeroes.Remove(ToRemoveHero);
        SaveGame();
    }
    AddHeroToParty(ToAddHero);*/
}

void USaveManager::AddHeroToParty(FHeroSaveData& ToAddHero)
{
    bool bAlreadyInParty = CurrentSaveGame->ActiveHeroes.ContainsByPredicate([&](const FHeroSaveData& Data)
        {
            return Data.EntityDataId.ToString().Equals(ToAddHero.EntityDataId.ToString());
        });
    //TODO Add a limit
    if (bAlreadyInParty)
    {
        UE_LOG(LogTemp, Log, TEXT("Hero %s is already in active Party"), *ToAddHero.EntityDataId.ToString());
        return;
    }
    CurrentSaveGame->ActiveHeroes.Add(ToAddHero);
    SaveGame();
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
