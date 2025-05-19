// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIManager.h"
#include "BattleManager.h"
#include "SaveManager.h"
#include "COTDDamageManager.h"
#include "Engine/GameInstance.h"
#include "COTDGameInstance.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EGameModeType : uint8
{
	None UMETA(DisplayName = "None"),
	Quickplay UMETA(DisplayName = "Quickplay"),
	Endless UMETA(DisplayName = "Endless"),
};

USTRUCT(BlueprintType)
struct PROJECTCOTD_API FCombatDatas
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	bool Victory = false;

	UPROPERTY(BlueprintReadWrite)
	int32 EnnemyKill = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 AllyDeath = 0;

	/*** Passed As Data Between scen ***/

	UPROPERTY(BlueprintReadWrite)
	EGameModeType Mode;

	//For endless mode only
	UPROPERTY(BlueprintReadWrite)
	int32 CurrentEndlessDepth = 0;

	//For Endless mode Only
	UPROPERTY(BlueprintReadWrite)
	FMapNode MapNodeSelected;

	/*** Calculated Post game ***/

	//For endless mode only
	UPROPERTY(BlueprintReadOnly)
	float EndlessMoney = 0;

};

UCLASS()
class PROJECTCOTD_API UCOTDGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:

	/*********** ATTRIBUTES *************/

	/* Managers */
	UPROPERTY(BlueprintReadOnly, Category = "Managers")
	UUIManager* UIManager;
	UPROPERTY(BlueprintReadOnly, Category = "Managers")
	UBattleManager* BattleManager;
	UPROPERTY(BlueprintReadOnly, Category = "Managers")
	UCOTDDamageManager* DamageManager;
	UPROPERTY(BlueprintReadOnly, Category = "Managers")
	USaveManager* SaveManager;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUIManager> UIManagerClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Battle")
	TSubclassOf<UBattleManager> BattleManagerClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Color")
	TSubclassOf<UCOTDDamageManager> DamagerManagerClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Save")
	TSubclassOf<USaveManager> SaveManagerClass;

	/* Combat Section */
	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	EGameModeType CurrentGameMode;

	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	FCombatDatas CombatResult;

	/* Endless mode utils */

	/*********** FUNCTIONS *************/

	virtual void Init() override;

	/* World */
	UFUNCTION(BlueprintCallable, Category = "World")
	void UpdateWorld();

	/* Combat Section */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetGameMode(EGameModeType GameMode)
	{
		CurrentGameMode = GameMode;
	}

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ResetCombatResult();

	//Should be called at the end of the battle
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ComputeCombatResult();
};
