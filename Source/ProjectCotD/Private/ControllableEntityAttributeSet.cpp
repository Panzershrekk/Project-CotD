// Fill out your copyright notice in the Description page of Project Settings.


#include "ControllableEntityAttributeSet.h"
#include "GameplayEffectExtension.h" 
void UControllableEntityAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);
    if (Data.EvaluatedData.Attribute == GetExperienceAttribute())
    {
        float CurrentXP = GetExperience();
        float RequiredXP = GetExperienceToLevelUp();

        if (CurrentXP >= RequiredXP)
        {
            float NewLevel = GetLevel() + 1;
            SetLevel(NewLevel);

            SetUnassignedStatPoints(GetUnassignedStatPoints() + 3);

            SetExperience(0);

            float NewXPRequired = (NewLevel == 2) ? 50 : RequiredXP * 1.5f;
            SetExperienceToLevelUp(NewXPRequired);
        }
    }
}