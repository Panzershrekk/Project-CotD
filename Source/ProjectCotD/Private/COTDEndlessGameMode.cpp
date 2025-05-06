// Fill out your copyright notice in the Description page of Project Settings.


#include "COTDEndlessGameMode.h"

void ACOTDEndlessGameMode::InitRun()
{
	InitRunWithGivenSeed(GenerateRandomSeed());
}

void ACOTDEndlessGameMode::InitRunWithGivenSeed(int32 Seed)
{
	CurrentRunState.Depth = 0;
	CurrentRunState.Gold = 0;
	CurrentRunState.Seed = Seed;
}

void ACOTDEndlessGameMode::GenerateRowAtDepth(int32 Depth)
{
}

void ACOTDEndlessGameMode::StartCombat(const FMapNode& Node)
{
    /*auto GI = Cast<UEndlessGameInstance>(GetGameInstance());
    GI->CurrentRun.Depth = Node.Depth;
    GI->CurrentRun.Buffs.Append(Node.MapModifiers);
    UGameplayStatics::OpenLevel(this, TEXT("CombatLevel"));*/
}