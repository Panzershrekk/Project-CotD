// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageColorManager.h"

void UDamageColorManager::Initialize(UCOTDGameInstance* Instance)
{
    COTDGameInstance = Instance;
}

FLinearColor UDamageColorManager::GetColorForDamageType(ESubDamagerType SubDamageType) const
{
    if (!DamageColorDataTable) return FColor::White;

    static const FString ContextString(TEXT("DamageColor"));
    const FName RowName = FName(*UEnum::GetDisplayValueAsText(SubDamageType).ToString());
    FDamageColorInfo* FoundRow = DamageColorDataTable->FindRow<FDamageColorInfo>(RowName, ContextString);

    return FoundRow ? FoundRow->DamageColor : FColor::White;
}