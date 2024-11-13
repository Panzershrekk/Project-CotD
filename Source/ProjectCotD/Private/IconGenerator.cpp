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

//Exemple of use -> https://forums.unrealengine.com/t/updatetextureregions-pitch/427713

UTexture2D* AIconGenerator::ConvertRenderTargetToTexture2D(UTextureRenderTarget2D* RenderTarget)
{
    if (!RenderTarget)
    {
        UE_LOG(LogTemp, Error, TEXT("RenderTarget is null"));
        return nullptr;
    }

    const int32 Width = RenderTarget->SizeX;
    const int32 Height = RenderTarget->SizeY;
    if (Width != Height)
    {
        UE_LOG(LogTemp, Error, TEXT("Dimension must bu equal, current: Width=%d, Height=%d"), Width, Height);
    }

    TArray<FColor> OutBMP;
    FRenderTarget* RenderTargetResource = RenderTarget->GameThread_GetRenderTargetResource();
    RenderTargetResource->ReadPixels(OutBMP);

    if (OutBMP.Num() != Width * Height)
    {
        UE_LOG(LogTemp, Error, TEXT("Dimension must bu equal, current: Width=%d, Height=%d"), Width, Height);
        return nullptr;
    }

    //TODO: Change that, quick fix because transparency was 0, no matter what
    for (int j = 0; j < OutBMP.Num(); j++)
    {
        OutBMP[j].A = 255;
    }

    UTexture2D* Texture = UTexture2D::CreateTransient(Width, Height, PF_B8G8R8A8);
    if (!Texture)
    {
        UE_LOG(LogTemp, Error, TEXT("Cannot create transient texture"));
        return nullptr;
    }
    Texture->CompressionSettings = TC_Default;
    Texture->SRGB = RenderTarget->SRGB;
    Texture->UpdateResource();


    if (Texture->GetSizeX() != Width || Texture->GetSizeY() != Height)
    {
        UE_LOG(LogTemp, Error, TEXT("Texture size is wrong : Width=%d, Height=%d, TextureWidth=%d, TextureHeight=%d"),
            Width, Height, Texture->GetSizeX(), Texture->GetSizeY());
        return nullptr;
    }

    FUpdateTextureRegion2D* Region = new FUpdateTextureRegion2D(0, 0, 0, 0, Width, Height);
    TFunction<void(uint8* SrcData, const FUpdateTextureRegion2D* Regions)> DataCleanupFunc =
        [](uint8* SrcData, const FUpdateTextureRegion2D* Regions) {
        delete[] SrcData;
        delete[] Regions;
        };

    Texture->UpdateTextureRegions(0, 1, Region, Width * sizeof(FColor), sizeof(FColor), (uint8*)OutBMP.GetData(), DataCleanupFunc);
    //Texture->UpdateTextureRegions(0, 1, Region, Width * sizeof(FColor), sizeof(FColor), reinterpret_cast<uint8*>(OutBMP.GetData()));

    return Texture;
}
