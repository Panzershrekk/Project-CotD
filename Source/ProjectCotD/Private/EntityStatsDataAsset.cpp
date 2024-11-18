// Fill out your copyright notice in the Description page of Project Settings.


#include "EntityStatsDataAsset.h"

UFUNCTION(BlueprintCallable, Category = "Spells")
TArray<UCOTDGameplayAbility*> UEntityStatsDataAsset::GetAbilitiesDataAssets() const
{
    TArray<UCOTDGameplayAbility*> Abilities;
    for (TSubclassOf<UCOTDGameplayAbility> SpellClass : EntitySpells)
    {
        if (SpellClass)
        {
            // Crée une instance temporaire à partir de la classe pour accéder à ses propriétés
            UCOTDGameplayAbility* TempAbility = SpellClass->GetDefaultObject<UCOTDGameplayAbility>();
            if (TempAbility)
            {
                Abilities.Add(TempAbility);
            }
        }
    }
    return Abilities;
}