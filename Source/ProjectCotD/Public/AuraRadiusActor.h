// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameplayEffectAura.h"
#include "COTDAbilitySystemComponent.h"
#include "GameFramework/Actor.h"
#include "AuraRadiusActor.generated.h"

/**
 *
 */

UCLASS()
class PROJECTCOTD_API AAuraRadiusActor : public AActor
{
	GENERATED_BODY()
	
public:
    AAuraRadiusActor();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, Category = "Aura")
    UCapsuleComponent* AuraCapsule;

    UPROPERTY()
    AActor* OwnerActor;

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
        const FHitResult& SweepResult);

    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
        

public:
    void Initialize(AActor* InOwner, UGameplayEffectAura& AuraEffect);

};
