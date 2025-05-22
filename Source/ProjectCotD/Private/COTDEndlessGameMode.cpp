// Fill out your copyright notice in the Description page of Project Settings.


#include "COTDEndlessGameMode.h"

void ACOTDEndlessGameMode::InitClass(UCOTDGameInstance* GameInstance)
{
    GI = GameInstance;
    if (GI)
    {
        SaveManager = GI->SaveManager;
    }
}

void ACOTDEndlessGameMode::InitRun()
{
	InitRunWithGivenSeed(GenerateRandomSeed());
}

void ACOTDEndlessGameMode::InitRunWithGivenSeed(int32 Seed)
{
    if (SaveManager)
    {
        SaveManager->CreateNewRunWithSeed(Seed);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Save Manager is Null"));
    }
}

void ACOTDEndlessGameMode::ProcessCombatResult()
{
    if (GI && SaveManager)
    {
        const FCombatDatas& Result = GI->CombatResult;
        FEndlessRunState UpdatedState = SaveManager->GetCurrentSaveGame()->EndlessRunState;
        if (Result.Victory == true)
        {
            UpdatedState.EndlessCurrency += Result.EndlessMoney;
            UpdatedState.Depth += 1;
        }
        SaveManager->SaveEndlessRunState(UpdatedState);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Intance or SaveManager is Null"));
    }
}

TArray<FMapNode> ACOTDEndlessGameMode::GenerateRowAtDepth(int32 Depth)
{
    FRandomStream RNG(SaveManager->GetCurrentSaveGame()->EndlessRunState.Seed);
    TArray<FMapNode> Nodes;
    Nodes.Reserve(3);

    for (int32 i = 0; i < 3; ++i)
    {
        FMapNode Node;
        Node.Depth = Depth;

        Node.NodeID = FGuid::NewGuid();

        //Generation
        for (int32 j = 0; j < Node.Depth + 1; ++j)
        {
            if (PossiblesAffixesForEnemy.Num() > 0)
            {
                int32 Index = RNG.RandRange(0, PossiblesAffixesForEnemy.Num() - 1);
                FEndlessRunBuff RandomBuff = PossiblesAffixesForEnemy[Index];

                AddEnemyBuffOnNode(Node, RandomBuff);
            }
            UE_LOG(LogTemp, Warning, TEXT("Node has %d effect(s)"), Node.MapEnnemiesBuff.Num());
        }
        //End Gen

        Nodes.Add(Node);
    }
    return Nodes;
}

void ACOTDEndlessGameMode::AddEnemyBuffOnNode(FMapNode& MapNode, const FEndlessRunBuff& MapEnemyBuff)
{

    if (!MapEnemyBuff.GameplayEffectClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("Buff is invalid: GameplayEffectClass is null"));
        return;
    }
    TSubclassOf<UGameplayEffect> BuffEffect = MapEnemyBuff.GameplayEffectClass;
    int32 Count = MapEnemyBuff.StackCount;
    bool bUnique = MapEnemyBuff.bUnique;

    for (FEndlessRunBuff& Buff : MapNode.MapEnnemiesBuff)
    {
        if (Buff.GameplayEffectClass == BuffEffect)
        {
            if (!Buff.bUnique)
            {
                Buff.StackCount += Count;
            }
            return;
        }
    }

    FEndlessRunBuff NewBuff;
    NewBuff.GameplayEffectClass = BuffEffect;
    NewBuff.StackCount = Count;
    NewBuff.bUnique = bUnique;
    MapNode.MapEnnemiesBuff.Add(MapEnemyBuff);
}

/*GI = Cast<UCOTDGameInstance>(SourceActor->GetWorld()->GetGameInstance());
if (GI == nullptr)
{*/
//UE_LOG(LogTemp, Warning, TEXT("Instance is null"));
//}