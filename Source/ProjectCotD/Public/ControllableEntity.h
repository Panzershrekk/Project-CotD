// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EntityStatsDataAsset.h"
#include "COTDAbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/ArrowComponent.h"
#include "DOTEffectExecutionCalculation.h"
#include "GameFramework/Character.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ControllableEntity.generated.h"

UCLASS()
class PROJECTCOTD_API AControllableEntity : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
	bool bHasRolledInitiative = false;
	float RolledInitative = 0.f;

public:
	// Sets default values for this pawn's properties
	AControllableEntity();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	UEntityStatsDataAsset* EntityStatsDataAsset;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	UCOTDAbilitySystemComponent* AbilitySystemComponent;

	virtual UCOTDAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return AbilitySystemComponent;
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	const class UControllableEntityAttributeSet* ControllableEntityAttributeSet;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	int GetInitiative() const;
	void RollInitiative();

	UFUNCTION(BlueprintCallable, Category = "ConstructorSetup")
	void DataTableSetup();
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void HandleStartOfTurnEffect();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void DecreaseTurnRemainingOnOverTurnEffect();
};
