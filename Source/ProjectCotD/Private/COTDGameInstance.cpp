// Fill out your copyright notice in the Description page of Project Settings.


#include "COTDGameInstance.h"

void UCOTDGameInstance::Init()
{
    Super::Init();
    if (UIManagerClass)
    {
        UIManager = NewObject<UUIManager>(this, UIManagerClass);
        if (UIManager)
        {
            UIManager->Initialize(GetWorld(), this);
        }
    }
    if (BattleManagerClass)
    {
        BattleManager = NewObject<UBattleManager>(this, BattleManagerClass);
        if (BattleManager)
        {
            BattleManager->Initialize(this);
        }
    }

    if (DamagerManagerClass)
    {
        DamageManager = NewObject<UCOTDDamageManager>(this, DamagerManagerClass);
        if (DamageManager)
        {
            DamageManager->Initialize(this);
        }
    }
    if (SaveManagerClass)
    {
        SaveManager = NewObject<USaveManager>(this, SaveManagerClass);
        if (SaveManager)
        {
            SaveManager->Initialize(this);
        }
    }
}

void UCOTDGameInstance::UpdateWorld()
{
    if (UIManager)
    {
        UIManager->Initialize(GetWorld(), this);
    }
}

void UCOTDGameInstance::ResetCombatResult()
{
    CombatResult = FCombatResult();
}

void UCOTDGameInstance::ComputeCombatResult()
{
    float PerformanceScore = 0.f;
    
    PerformanceScore = CombatResult.EnnemyKill * 20 * (CombatResult.CurrentEndlessDepth + 1);
    if (CombatResult.Victory == false)
    {
        PerformanceScore *= 0;
    }
    CombatResult.EndlessMoney = PerformanceScore;
}
