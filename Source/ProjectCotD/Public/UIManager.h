// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UIManager.generated.h"

UCLASS(Blueprintable, BlueprintType)
class PROJECTCOTD_API UUIManager : public UObject
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<AActor> DefaultFloatingTextClass;

	// Sets default values for this actor's properties
	UUIManager();
	void ShowHealthChangeFloating(const FVector& Location, const FString& Text);
	void Initialize(UWorld* World);
private:
	UWorld* CachedWorld;
};
