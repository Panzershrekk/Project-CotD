// Fill out your copyright notice in the Description page of Project Settings.


#include "ControllableEntity.h"
#include "ControllableEntityAttributeSet.h"

// Sets default values
AControllableEntity::AControllableEntity()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
    RootComponent = CapsuleComponent;

    Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(RootComponent);

    ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
    ArrowComponent->SetupAttachment(RootComponent);

    CharacterMovement = CreateDefaultSubobject<UCharacterMovementComponent>(TEXT("CharacterMovement"));
    AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
}

// Called when the game starts or when spawned
void AControllableEntity::BeginPlay()
{
	Super::BeginPlay();
    if (IsValid(AbilitySystemComponent))
    {
        ControllableEntityAttributeSet = AbilitySystemComponent->GetSet<UControllableEntityAttributeSet>();
    }
}

// Called every frame
void AControllableEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AControllableEntity::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

int AControllableEntity::GetInitiative() const
{
    if (EntityStatsDataAsset)
    {
        return EntityStatsDataAsset->Initiative + FMath::RandRange(-EntityStatsDataAsset->InitiativeVariation, EntityStatsDataAsset->InitiativeVariation);
    }
    return 0;
}

