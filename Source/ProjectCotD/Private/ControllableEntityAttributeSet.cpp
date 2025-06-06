// Fill out your copyright notice in the Description page of Project Settings.


#include "ControllableEntityAttributeSet.h"
#include "GameplayEffectExtension.h" 

void UControllableEntityAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
    {
        /*float CurrentXP = GetExperience();

        if (CurrentXP >= RequiredXP)
        {
            float NewLevel = GetLevel() + 1;
            SetLevel(NewLevel);

            SetUnassignedStatPoints(GetUnassignedStatPoints() + 3);

            SetExperience(0);

            float NewXPRequired = (NewLevel == 2) ? 50 : RequiredXP * 1.5f;
            SetExperienceToLevelUp(NewXPRequired);
        }*/
    }
}