// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIManager.h"
#include "BattleManager.h"
#include "DamageColorManager.h"
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
	UDamageColorManager* DamageColorManager;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUIManager> UIManagerClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Battle")
	TSubclassOf<UBattleManager> BattleManagerClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Color")
	TSubclassOf<UDamageColorManager> DamageColorManagerClass;

	virtual void Init() override;
	UFUNCTION(BlueprintCallable, Category = "World")
	void UpdateWorld();
};
