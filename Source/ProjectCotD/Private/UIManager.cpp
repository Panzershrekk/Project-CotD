// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"
#include "BattleFloatingText.h"

// Sets default values
UUIManager::UUIManager()
{

}

void UUIManager::ShowHealthChangeFloating(const FVector& Location, const FString& Text)
{
    if (!CachedWorld) return;

    ABattleFloatingText* FloatingText = CachedWorld->SpawnActor<ABattleFloatingText>(DefaultFloatingTextClass, Location + FVector(0, 0, 100), FRotator::ZeroRotator);
    if (FloatingText)
    {
        FloatingText->Initialize(Text); 
    }
}

void UUIManager::Initialize(UWorld* World)
{
    this->CachedWorld = World;
}