// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageColorManager.h"

void UDamageColorManager::Initialize(UCOTDGameInstance* Instance)
{
    COTDGameInstance = Instance;
}

FLinearColor UDamageColorManager::GetColorForDamageType(ESubDamagerType SubDamageType) const
{
    if (!DamageColorDataTable) return FLinearColor::White;

    static const FString ContextString(TEXT("Damage Color"));
    FDamageColorInfo* FoundRow = DamageColorDataTable->FindRow<FDamageColorInfo>(
        FName(*UEnum::GetValueAsString(SubDamageType)), ContextString);

    return FoundRow ? FoundRow->DamageColor : FLinearColor::White;
}