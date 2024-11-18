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
            // Cr�e une instance temporaire � partir de la classe pour acc�der � ses propri�t�s
            UCOTDGameplayAbility* TempAbility = SpellClass->GetDefaultObject<UCOTDGameplayAbility>();
            if (TempAbility)
            {
                Abilities.Add(TempAbility);
            }
        }
    }
    return Abilities;
}