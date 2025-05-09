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

TArray<FMapNode> ACOTDEndlessGameMode::GenerateRowAtDepth(int32 Depth)
{
    //FRandomStream RNG(CurrentRunState.Seed);
    TArray<FMapNode> Nodes;
    Nodes.Reserve(3);

    for (int32 i = 0; i < 3; ++i)
    {
        FMapNode Node;
        Node.Depth = Depth;

        Node.NodeID = FGuid::NewGuid();
        Nodes.Add(Node);
    }
    return Nodes;
}

void ACOTDEndlessGameMode::StartCombat(const FMapNode& Node)
{
    /*auto GI = Cast<UEndlessGameInstance>(GetGameInstance());
    GI->CurrentRun.Depth = Node.Depth;
    GI->CurrentRun.Buffs.Append(Node.MapModifiers);
    UGameplayStatics::OpenLevel(this, TEXT("CombatLevel"));*/
}

/*GI = Cast<UCOTDGameInstance>(SourceActor->GetWorld()->GetGameInstance());
if (GI == nullptr)
{*/
//UE_LOG(LogTemp, Warning, TEXT("Instance is null"));
//}