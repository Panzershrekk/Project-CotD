// Fill out your copyright notice in the Description page of Project Settings.


#include "EntityStatsDataAsset.h"

UFUNCTION(BlueprintCallable, Category = "Spells")
TArray<UAbilitiesDataAsset*> UEntityStatsDataAsset::GetAbilitiesDataAssets() const
{
    TArray<UAbilitiesDataAsset*> DataAssets;
    for (TSubclassOf<UCOTDGameplayAbility> SpellClass : EntitySpells)
    {
        if (SpellClass)
        {
            // Crée une instance temporaire pour accéder aux propriétés
            UCOTDGameplayAbility* TempAbility = SpellClass->GetDefaultObject<UCOTDGameplayAbility>();
            if (TempAbility && TempAbility->AbilitiesDataAsset)
            {
                DataAssets.Add(TempAbility->AbilitiesDataAsset);
            }
        }
    }
    return DataAssets;
}