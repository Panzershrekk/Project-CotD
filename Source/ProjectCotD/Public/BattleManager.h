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
	bool isbattleStarted;
	UPROPERTY(BlueprintReadOnly, Category = "Battle")
	int currentTurn;


	UPROPERTY(BlueprintReadOnly, Category = "Battle")
	TArray<AControllableEntity*> allControllableEntities;
	UPROPERTY(BlueprintReadOnly, Category = "Battle")
	TArray<AControllableEntity*> orderOfPlayList;
	//---> PSeudo code
// 
	//List<CurentPlayable> all entities
	//List<OrdererPlayeble> initiative

	UFUNCTION(BlueprintCallable, Category = "BattleFlow")
	void StartCombat(TArray<AControllableEntity*> controllabledEntities);

	UFUNCTION(BlueprintCallable, Category = "BattleFlow")
	AControllableEntity* DefineNextPlayableEntity(AControllableEntity* CurrentPlaying);
	void CheckForBattleEnd();
	UFUNCTION(BlueprintImplementableEvent, Category = "Battle")
	void ApplyDamageToEntityAndUpdateUI(const AActor* ControllableEntity);
};
