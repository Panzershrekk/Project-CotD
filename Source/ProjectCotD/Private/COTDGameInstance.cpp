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

    if (DamageColorManagerClass)
    {
        DamageColorManager = NewObject<UDamageColorManager>(this, DamageColorManagerClass);
        if (DamageColorManager)
        {
            DamageColorManager->Initialize(this);
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
