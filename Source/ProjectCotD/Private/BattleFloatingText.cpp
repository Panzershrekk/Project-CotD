// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleFloatingText.h"

// Sets default values
ABattleFloatingText::ABattleFloatingText()
{

	TextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRender"));

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	TextRender->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABattleFloatingText::BeginPlay()
{
	Super::BeginPlay();
}

void ABattleFloatingText::Initialize(const FString& Text)
{
	if (TextRender)
	{
		TextRender->SetText(FText::FromString(Text));
	}
}

void ABattleFloatingText::Initialize(const FDamagerDisplayInfo& Displayer)
{
	if (TextRender)
	{
		TextRender->SetTextRenderColor(Displayer.DisplayColor.ToFColor(true));
		TextRender->SetText(FText::FromString(FString::FromInt(Displayer.DamageDone)));
	}
}


