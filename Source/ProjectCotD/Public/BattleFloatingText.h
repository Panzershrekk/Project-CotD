// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Actor.h"
#include "BattleFloatingText.generated.h"

UCLASS()
class PROJECTCOTD_API ABattleFloatingText : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABattleFloatingText();
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "TextRender")
	UTextRenderComponent* TextRender;
	void Initialize(const FString& Text);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
