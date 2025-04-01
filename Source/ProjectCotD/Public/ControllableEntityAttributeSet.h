// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "ControllableEntityAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


UCLASS()
class PROJECTCOTD_API UControllableEntityAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:

	//Health
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UControllableEntityAttributeSet, Health);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UControllableEntityAttributeSet, MaxHealth);



	//Mana
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UControllableEntityAttributeSet, Mana);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UControllableEntityAttributeSet, MaxMana);


	//Martial Point
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MartialPoint;
	ATTRIBUTE_ACCESSORS(UControllableEntityAttributeSet, MartialPoint);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxMartialPoint;
	ATTRIBUTE_ACCESSORS(UControllableEntityAttributeSet, MaxMartialPoint);



	//Martial Point
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MagicPoint;
	ATTRIBUTE_ACCESSORS(UControllableEntityAttributeSet, MagicPoint);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxMagicPoint;
	ATTRIBUTE_ACCESSORS(UControllableEntityAttributeSet, MaxMagicPoint);

	//Others Stats
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Initiative;
	ATTRIBUTE_ACCESSORS(UControllableEntityAttributeSet, Initiative);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData InitiativeVariation;
	ATTRIBUTE_ACCESSORS(UControllableEntityAttributeSet, InitiativeVariation);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData Movement;
	ATTRIBUTE_ACCESSORS(UControllableEntityAttributeSet, Movement);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxMovement;
	ATTRIBUTE_ACCESSORS(UControllableEntityAttributeSet, MaxMovement);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MainStats")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UControllableEntityAttributeSet, Strength);

	/*************************************  LEVELING  *************************************************************/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leveling")
	FGameplayAttributeData Experience;
	ATTRIBUTE_ACCESSORS(UControllableEntityAttributeSet, Experience);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leveling")
	FGameplayAttributeData ExperienceToLevelUp;
	ATTRIBUTE_ACCESSORS(UControllableEntityAttributeSet, ExperienceToLevelUp);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leveling")
	FGameplayAttributeData Level;
	ATTRIBUTE_ACCESSORS(UControllableEntityAttributeSet, Level);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leveling")
	FGameplayAttributeData UnassignedStatPoints;
	ATTRIBUTE_ACCESSORS(UControllableEntityAttributeSet, UnassignedStatPoints);


protected:
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
};
