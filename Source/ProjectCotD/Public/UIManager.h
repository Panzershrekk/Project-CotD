// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageColorInfo.h"
#include "GameFramework/Actor.h"
#include "UIManager.generated.h"

class UCOTDGameInstance;

UCLASS(Blueprintable, BlueprintType)
class PROJECTCOTD_API UUIManager : public UObject
{
	GENERATED_BODY()

public:	
	UPROPERTY(BlueprintReadOnly, Category = "Instance")
	UCOTDGameInstance* COTDGameInstance;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<AActor> DefaultFloatingTextClass;

	// Sets default values for this actor's properties
	UUIManager();
	UFUNCTION(BlueprintImplementableEvent, Category = "Battle")
	void UpdateHealth(const AActor* ControllableEntity);

	UFUNCTION(BlueprintCallable, Category = "Battle")
	void CallUpdateHealth(const AActor* ControllableEntity)
	{
		UpdateHealth(ControllableEntity);
	}

	void ShowHealthChangeFloating(const FVector& Location, const FString& Text);
	void ShowHealthChangeFloating(const FVector& Location, TQueue<FDamagerDisplayInfo>& DisplayerInfo);
	void Initialize(UWorld* World, UCOTDGameInstance* Instance);
private:
	UWorld* CachedWorld;
};
