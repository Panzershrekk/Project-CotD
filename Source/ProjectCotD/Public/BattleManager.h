// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ControllableEntity.h"
#include "GameFramework/Actor.h"
#include "BattleManager.generated.h"

class UCOTDGameInstance;

UCLASS(Blueprintable, BlueprintType)
class PROJECTCOTD_API UBattleManager : public UObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UBattleManager();
	void Initialize(UCOTDGameInstance* Instance);

	UPROPERTY(BlueprintReadOnly, Category = "Battle")
	UCOTDGameInstance* COTDGameInstance;
	UPROPERTY(BlueprintReadOnly, Category = "Battle")
	bool IsbattleStarted;
	UPROPERTY(BlueprintReadOnly, Category = "Battle")
	int CurrentTurn;


	UPROPERTY(BlueprintReadOnly, Category = "Battle")
	TArray<AControllableEntity*> AllControllableEntities;
	UPROPERTY(BlueprintReadOnly, Category = "Battle")
	TArray<AControllableEntity*> OrderOfPlayList;

	UFUNCTION(BlueprintCallable, Category = "BattleFlow")
	void StartCombat();
	UFUNCTION(BlueprintCallable, Category = "BattleFlow")
	void AddEntityByInitiative(AControllableEntity* NewEntity);
	//This will remove the entity from the fight but it will still be physicaly here, for ressurection/necromancy kind of effect
	UFUNCTION(BlueprintCallable, Category = "BattleFlow")
	void RemoveEntityFromPlay(AControllableEntity* EntityToRemove);
	UFUNCTION(BlueprintCallable, Category = "BattleFlow")
	AControllableEntity* DefineNextPlayableEntity(AControllableEntity* CurrentPlaying);
	void CheckForBattleEnd();
	//No need to be coded in cpp
	UFUNCTION(BlueprintImplementableEvent, Category = "Battle")
	void ApplyDamageToEntityAndUpdateUI(const AActor* ControllableEntity);
};
