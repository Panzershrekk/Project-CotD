// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIManager.h"
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUIManager> UIManagerClass;

	virtual void Init() override;
};
