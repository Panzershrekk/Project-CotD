// Fill out your copyright notice in the Description page of Project Settings.


#include "COTDDamageManager.h"

void UCOTDDamageManager::Initialize(UCOTDGameInstance* Instance)
{
    COTDGameInstance = Instance;
}

FLinearColor UCOTDDamageManager::GetColorForDamageType(FGameplayTag DamageTag) const
{
    if (!DamageDataTable) 
        return FColor::White;

    static const FString ContextString(TEXT("DamageColor"));
    const FName RowName = FName(DamageTag.ToString());
    FDamageColorInfo* FoundRow = DamageDataTable->FindRow<FDamageColorInfo>(RowName, ContextString);

    return FoundRow ? FoundRow->DamageColor : FColor::White;
}


float UCOTDDamageManager::GetMultiplierFromTag(FGameplayTag DamageTag, const UAbilitySystemComponent* ASC) const
{
    if (!DamageDataTable)
        return 0.0f;
    static const FString ContextString(TEXT("AttributeMultiplier"));
    const FName RowName = FName(DamageTag.ToString());
    FDamageColorInfo* FoundRow = DamageDataTable->FindRow<FDamageColorInfo>(RowName, ContextString);

    if (ASC && FoundRow)
    {
        return ASC->GetNumericAttribute(FoundRow->AttributeMultiplier);
    }
    UE_LOG(LogTemp, Warning, TEXT("DamageTag %f couldn't be found"), DamageTag.GetTagName());
    return 0.0f;
}