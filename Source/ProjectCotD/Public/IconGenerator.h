// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Engine/Texture2D.h"              
#include "RenderUtils.h"                   
#include "Runtime/Engine/Classes/Engine/TextureRenderTarget.h"
#include "Engine/Texture.h"
#include "ImageUtils.h"
#include "GameFramework/Actor.h"
#include "IconGenerator.generated.h"

UCLASS()
class PROJECTCOTD_API AIconGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIconGenerator();
	UFUNCTION(BlueprintCallable, Category = "Icon gen")
	UTexture2D* ConvertRenderTargetToTexture2D(UTextureRenderTarget2D* RenderTarget);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
