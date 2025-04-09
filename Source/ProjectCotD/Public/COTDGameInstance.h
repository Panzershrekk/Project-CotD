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
UCLASS()
class PROJECTCOTD_API UCOTDGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
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

	virtual void Init() override;
	UFUNCTION(BlueprintCallable, Category = "World")
	void UpdateWorld();
};
