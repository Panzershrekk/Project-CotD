// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"
#include "BattleFloatingText.h"

// Sets default values
UUIManager::UUIManager()
{

}

void UUIManager::ShowHealthChangeFloating(const FVector& Location, const FDamagerDisplayInfo& DisplayerInfo)
{
    if (!CachedWorld) return;

    ABattleFloatingText* FloatingText = CachedWorld->SpawnActor<ABattleFloatingText>(DefaultFloatingTextClass, Location + FVector(0, 0, 100), FRotator::ZeroRotator);
    if (FloatingText)
    {
        FloatingText->Initialize(DisplayerInfo);
    }
}

void UUIManager::ShowHealthChangeFloating(const FVector& Location, TQueue<FDamagerDisplayInfo>& DisplayerInfo)
{
    if (!CachedWorld) return;
    double offset = 0;//TMP
    while (!DisplayerInfo.IsEmpty())
    {
        FDamagerDisplayInfo DisplayInfo;
        if (DisplayerInfo.Peek(DisplayInfo) && DefaultFloatingTextClass)
        {
            ABattleFloatingText* FloatingText = CachedWorld->SpawnActor<ABattleFloatingText>(DefaultFloatingTextClass, Location + FVector(0, 0, 100 + offset), FRotator::ZeroRotator);
            offset += 150;
            if (FloatingText)
            {
                FloatingText->Initialize(DisplayInfo);
            }
            DisplayerInfo.Dequeue(DisplayInfo);
        }
        else
        {
            break;
        }
    }
}

void UUIManager::Initialize(UWorld* World, UCOTDGameInstance* Instance)
{
    COTDGameInstance = Instance;
    this->CachedWorld = World;
}