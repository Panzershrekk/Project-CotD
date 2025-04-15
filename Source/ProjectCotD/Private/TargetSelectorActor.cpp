// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetSelectorActor.h"

// Sets default values
ATargetSelectorActor::ATargetSelectorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATargetSelectorActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATargetSelectorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

