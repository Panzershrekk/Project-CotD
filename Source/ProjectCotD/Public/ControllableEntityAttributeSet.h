// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "ControllableEntityAttributeSet.generated.h"

/*
******************************************************************
******************************************************************
******************************************************************
******************************************************************
****     !!!!WARNING WARNING WARNING WARNING WARNING !!!!     ****
****		DONT FORGET TO ADD ANY ATTRIBUTE ADDED            ****
****		 TO THE SAVE FILE STRUCT IF NECESSARY             ****
****														  ****
****														  ****
******************************************************************
******************************************************************
******************************************************************
******************************************************************
*/

USTRUCT(BlueprintType)
struct FHeroSaveData
{
	GENERATED_BODY()

	UPROPERTY()
	FString HeroID;

	// Leveling
	UPROPERTY() int32 Level;
	UPROPERTY() float Experience;
	UPROPERTY() float UnassignedStatPoints;

	// Health, Mana, Martial, Magic
	UPROPERTY() float Health;
	UPROPERTY() float MaxHealth;
	UPROPERTY() float Mana;
	UPROPERTY() float MaxMana;
	UPROPERTY() float MartialPoint;
	UPROPERTY() float MaxMartialPoint;
	UPROPERTY() float MagicPoint;
	UPROPERTY() float MaxMagicPoint;

	// Movement / Initiative
	UPROPERTY() float Initiative;
	UPROPERTY() float InitiativeVariation;
	UPROPERTY() float Movement;
	UPROPERTY() float MaxMovement;

	// Main Stats
	UPROPERTY() float Strength;
	UPROPERTY() float Intelligence;
	UPROPERTY() float Stamina;

	// Damage Multipliers
	UPROPERTY() float DamageMultiplier;
	UPROPERTY() float PhysicalDamageMultiplier;
	UPROPERTY() float MagicalDamageMultiplier;
	UPROPERTY() float BluntDamageMultiplier;
	UPROPERTY() float PiercingDamageMultiplier;
	UPROPERTY() float SlashDamageMultiplier;
	UPROPERTY() float FireDamageMultiplier;
	UPROPERTY() float FrostDamageMultiplier;
	UPROPERTY() float NatureDamageMultiplier;
	UPROPERTY() float ShadowDamageMultiplier;
	UPROPERTY() float LightDamageMultiplier;
	UPROPERTY() float ArcaneDamageMultiplier;
	UPROPERTY() float PoisonDamageMultiplier;

	// Utility
	void FromAttributeSet(const class UControllableEntityAttributeSet* AttrSet)
	{
		if (!AttrSet) return;

		Level = AttrSet->Level.GetCurrentValue();
		Experience = AttrSet->Experience.GetCurrentValue();
		UnassignedStatPoints = AttrSet->UnassignedStatPoints.GetCurrentValue();

		Health = AttrSet->Health.GetCurrentValue();
		MaxHealth = AttrSet->MaxHealth.GetCurrentValue();
		Mana = AttrSet->Mana.GetCurrentValue();
		MaxMana = AttrSet->MaxMana.GetCurrentValue();
		MartialPoint = AttrSet->MartialPoint.GetCurrentValue();
		MaxMartialPoint = AttrSet->MaxMartialPoint.GetCurrentValue();
		MagicPoint = AttrSet->MagicPoint.GetCurrentValue();
		MaxMagicPoint = AttrSet->MaxMagicPoint.GetCurrentValue();

		Initiative = AttrSet->Initiative.GetCurrentValue();
		InitiativeVariation = AttrSet->InitiativeVariation.GetCurrentValue();
		Movement = AttrSet->Movement.GetCurrentValue();
		MaxMovement = AttrSet->MaxMovement.GetCurrentValue();

		Strength = AttrSet->Strength.GetCurrentValue();
		Intelligence = AttrSet->Intelligence.GetCurrentValue();
		Stamina = AttrSet->Stamina.GetCurrentValue();

		DamageMultiplier = AttrSet->DamageMultiplier.GetCurrentValue();
		PhysicalDamageMultiplier = AttrSet->PhysicalDamageMultiplier.GetCurrentValue();
		MagicalDamageMultiplier = AttrSet->MagicalDamageMultiplier.GetCurrentValue();
		BluntDamageMultiplier = AttrSet->BluntDamageMultiplier.GetCurrentValue();
		PiercingDamageMultiplier = AttrSet->PiercingDamageMultiplier.GetCurrentValue();
		SlashDamageMultiplier = AttrSet->SlashDamageMultiplier.GetCurrentValue();
		FireDamageMultiplier = AttrSet->FireDamageMultiplier.GetCurrentValue();
		FrostDamageMultiplier = AttrSet->FrostDamageMultiplier.GetCurrentValue();
		NatureDamageMultiplier = AttrSet->NatureDamageMultiplier.GetCurrentValue();
		ShadowDamageMultiplier = AttrSet->ShadowDamageMultiplier.GetCurrentValue();
		LightDamageMultiplier = AttrSet->LightDamageMultiplier.GetCurrentValue();
		ArcaneDamageMultiplier = AttrSet->ArcaneDamageMultiplier.GetCurrentValue();
		PoisonDamageMultiplier = AttrSet->PoisonDamageMultiplier.GetCurrentValue();
	}

	void ApplyToAttributeSet(class UControllableEntityAttributeSet* Attributes) const
	{
		Attributes->Level.SetBaseValue(Level);
		Attributes->Level.SetCurrentValue(Level);

		Attributes->Experience.SetBaseValue(Experience);
		Attributes->Experience.SetCurrentValue(Experience);

		Attributes->UnassignedStatPoints.SetBaseValue(UnassignedStatPoints);
		Attributes->UnassignedStatPoints.SetCurrentValue(UnassignedStatPoints);

		Attributes->Strength.SetBaseValue(Strength);
		Attributes->Strength.SetCurrentValue(Strength);

		Attributes->Intelligence.SetBaseValue(Intelligence);
		Attributes->Intelligence.SetCurrentValue(Intelligence);

		Attributes->Stamina.SetBaseValue(Stamina);
		Attributes->Stamina.SetCurrentValue(Stamina);

		Attributes->Health.SetBaseValue(Health);
		Attributes->Health.SetCurrentValue(Health);

		Attributes->MaxHealth.SetBaseValue(MaxHealth);
		Attributes->MaxHealth.SetCurrentValue(MaxHealth);

		Attributes->Mana.SetBaseValue(Mana);
		Attributes->Mana.SetCurrentValue(Mana);

		Attributes->MaxMana.SetBaseValue(MaxMana);
		Attributes->MaxMana.SetCurrentValue(MaxMana);

		Attributes->MartialPoint.SetBaseValue(MartialPoint);
		Attributes->MartialPoint.SetCurrentValue(MartialPoint);

		Attributes->MaxMartialPoint.SetBaseValue(MaxMartialPoint);
		Attributes->MaxMartialPoint.SetCurrentValue(MaxMartialPoint);

		Attributes->MagicPoint.SetBaseValue(MagicPoint);
		Attributes->MagicPoint.SetCurrentValue(MagicPoint);

		Attributes->MaxMagicPoint.SetBaseValue(MaxMagicPoint);
		Attributes->MaxMagicPoint.SetCurrentValue(MaxMagicPoint);

		Attributes->Initiative.SetBaseValue(Initiative);
		Attributes->Initiative.SetCurrentValue(Initiative);

		Attributes->InitiativeVariation.SetBaseValue(InitiativeVariation);
		Attributes->InitiativeVariation.SetCurrentValue(InitiativeVariation);

		Attributes->Movement.SetBaseValue(Movement);
		Attributes->Movement.SetCurrentValue(Movement);

		Attributes->MaxMovement.SetBaseValue(MaxMovement);
		Attributes->MaxMovement.SetCurrentValue(MaxMovement);

		Attributes->DamageMultiplier.SetBaseValue(DamageMultiplier);
		Attributes->DamageMultiplier.SetCurrentValue(DamageMultiplier);

		Attributes->PhysicalDamageMultiplier.SetBaseValue(PhysicalDamageMultiplier);
		Attributes->PhysicalDamageMultiplier.SetCurrentValue(PhysicalDamageMultiplier);

		Attributes->MagicalDamageMultiplier.SetBaseValue(MagicalDamageMultiplier);
		Attributes->MagicalDamageMultiplier.SetCurrentValue(MagicalDamageMultiplier);

		Attributes->BluntDamageMultiplier.SetBaseValue(BluntDamageMultiplier);
		Attributes->BluntDamageMultiplier.SetCurrentValue(BluntDamageMultiplier);

		Attributes->PiercingDamageMultiplier.SetBaseValue(PiercingDamageMultiplier);
		Attributes->PiercingDamageMultiplier.SetCurrentValue(PiercingDamageMultiplier);

		Attributes->SlashDamageMultiplier.SetBaseValue(SlashDamageMultiplier);
		Attributes->SlashDamageMultiplier.SetCurrentValue(SlashDamageMultiplier);

		Attributes->FireDamageMultiplier.SetBaseValue(FireDamageMultiplier);
		Attributes->FireDamageMultiplier.SetCurrentValue(FireDamageMultiplier);

		Attributes->FrostDamageMultiplier.SetBaseValue(FrostDamageMultiplier);
		Attributes->FrostDamageMultiplier.SetCurrentValue(FrostDamageMultiplier);

		Attributes->NatureDamageMultiplier.SetBaseValue(NatureDamageMultiplier);
		Attributes->NatureDamageMultiplier.SetCurrentValue(NatureDamageMultiplier);

		Attributes->ShadowDamageMultiplier.SetBaseValue(ShadowDamageMultiplier);
		Attributes->ShadowDamageMultiplier.SetCurrentValue(ShadowDamageMultiplier);

		Attributes->LightDamageMultiplier.SetBaseValue(LightDamageMultiplier);
		Attributes->LightDamageMultiplier.SetCurrentValue(LightDamageMultiplier);

		Attributes->ArcaneDamageMultiplier.SetBaseValue(ArcaneDamageMultiplier);
		Attributes->ArcaneDamageMultiplier.SetCurrentValue(ArcaneDamageMultiplier);

		Attributes->PoisonDamageMultiplier.SetBaseValue(PoisonDamageMultiplier);
		Attributes->PoisonDamageMultiplier.SetCurrentValue(PoisonDamageMultiplier);
	}
};



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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MainStats")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UControllableEntityAttributeSet, Intelligence);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MainStats")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UControllableEntityAttributeSet, Stamina);

	/*************************************  MULTIPLIER  *************************************************************/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BackgroundStats")
	FGameplayAttributeData DamageMultiplier;
	ATTRIBUTE_ACCESSORS(UControllableEntityAttributeSet, DamageMultiplier);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BackgroundStats")
	FGameplayAttributeData PhysicalDamageMultiplier;
	ATTRIBUTE_ACCESSORS(UControllableEntityAttributeSet, PhysicalDamageMultiplier);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BackgroundStats")
	FGameplayAttributeData MagicalDamageMultiplier;
	ATTRIBUTE_ACCESSORS(UControllableEntityAttributeSet, MagicalDamageMultiplier);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BackgroundStats")
	FGameplayAttributeData BluntDamageMultiplier;
	ATTRIBUTE_ACCESSORS(UControllableEntityAttributeSet, BluntDamageMultiplier);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BackgroundStats")
	FGameplayAttributeData PiercingDamageMultiplier;
	ATTRIBUTE_ACCESSORS(UControllableEntityAttributeSet, PiercingDamageMultiplier);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BackgroundStats")
	FGameplayAttributeData SlashDamageMultiplier;
	ATTRIBUTE_ACCESSORS(UControllableEntityAttributeSet, SlashDamageMultiplier);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BackgroundStats")
	FGameplayAttributeData FireDamageMultiplier;
	ATTRIBUTE_ACCESSORS(UControllableEntityAttributeSet, FireDamageMultiplier);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BackgroundStats")
	FGameplayAttributeData FrostDamageMultiplier;
	ATTRIBUTE_ACCESSORS(UControllableEntityAttributeSet, FrostDamageMultiplier);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BackgroundStats")
	FGameplayAttributeData NatureDamageMultiplier;
	ATTRIBUTE_ACCESSORS(UControllableEntityAttributeSet, NatureDamageMultiplier);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BackgroundStats")
	FGameplayAttributeData ShadowDamageMultiplier;
	ATTRIBUTE_ACCESSORS(UControllableEntityAttributeSet, ShadowDamageMultiplier);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BackgroundStats")
	FGameplayAttributeData LightDamageMultiplier;
	ATTRIBUTE_ACCESSORS(UControllableEntityAttributeSet, LightDamageMultiplier);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BackgroundStats")
	FGameplayAttributeData ArcaneDamageMultiplier;
	ATTRIBUTE_ACCESSORS(UControllableEntityAttributeSet, ArcaneDamageMultiplier);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BackgroundStats")
	FGameplayAttributeData PoisonDamageMultiplier;
	ATTRIBUTE_ACCESSORS(UControllableEntityAttributeSet, PoisonDamageMultiplier);
	/*************************************  LEVELING  *************************************************************/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leveling")
	FGameplayAttributeData Experience;
	ATTRIBUTE_ACCESSORS(UControllableEntityAttributeSet, Experience);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leveling")
	FGameplayAttributeData Level;
	ATTRIBUTE_ACCESSORS(UControllableEntityAttributeSet, Level);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Leveling")
	FGameplayAttributeData UnassignedStatPoints;
	ATTRIBUTE_ACCESSORS(UControllableEntityAttributeSet, UnassignedStatPoints);


protected:
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
};
