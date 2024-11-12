// Fill out your copyright notice in the Description page of Project Settings.


#include "IconGenerator.h"

// Sets default values
AIconGenerator::AIconGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AIconGenerator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIconGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UTexture2D* AIconGenerator::ConvertRenderTargetToTexture2D(UTextureRenderTarget2D* RenderTarget, UObject* Outer)
{
    if (!RenderTarget)
        return nullptr;

    UTexture2D* NewTexture = UTexture2D::CreateTransient(RenderTarget->SizeX, RenderTarget->SizeY, PF_B8G8R8A8);
    NewTexture->MipGenSettings = TMGS_NoMipmaps;
    NewTexture->SRGB = RenderTarget->SRGB;

    FTextureRenderTargetResource* RenderTargetResource = RenderTarget->GameThread_GetRenderTargetResource();
    FReadSurfaceDataFlags ReadPixelFlags(RCM_UNorm);
    ReadPixelFlags.SetLinearToGamma(false);

    TArray<FColor> OutBMP;
    //RenderTargetResource->ReadPixels(OutBMP, ReadPixelFlags);
    if (RenderTargetResource->ReadPixels(OutBMP, ReadPixelFlags))
    {
        UE_LOG(LogTemp, Log, TEXT("Pixels read successfully from RenderTarget."));
        if (OutBMP.Num() > 0)
        {
            UE_LOG(LogTemp, Log, TEXT("OutBMP has %d pixels. First pixel color: %s"), OutBMP.Num(), *OutBMP[0].ToString());
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("OutBMP is empty after reading pixels."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to read pixels from RenderTarget."));
    }
    FUpdateTextureRegion2D Region(0, 0, 0, 0, RenderTarget->SizeX, RenderTarget->SizeY);

    NewTexture->UpdateTextureRegions(0, 1, &Region,
        RenderTarget->SizeX * sizeof(FColor),
        sizeof(FColor),
        (uint8*)OutBMP.GetData());

    NewTexture->UpdateResource();
    UE_LOG(LogTemp, Log, TEXT("Texture2D updated with RenderTarget data."));

    return NewTexture;
}