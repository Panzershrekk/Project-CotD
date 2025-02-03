// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraRadiusActor.h"

// Sets default values
AAuraRadiusActor::AAuraRadiusActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    AuraCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("AuraCapsule"));
    AuraCapsule->SetupAttachment(RootComponent);

    AuraCapsule->SetCapsuleHalfHeight(10000.0f);
    AuraCapsule->SetCapsuleRadius(0.0f);

    AuraCapsule->OnComponentBeginOverlap.AddDynamic(this, &AAuraRadiusActor::OnOverlapBegin);
    AuraCapsule->OnComponentEndOverlap.AddDynamic(this, &AAuraRadiusActor::OnOverlapEnd);

}

// Called when the game starts or when spawned
void AAuraRadiusActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraRadiusActor::Initialize(AActor* InOwner, UGameplayEffectAura& Effect)
{
    OwnerActor = InOwner;
    if (OwnerActor)
    {
        AttachToActor(OwnerActor, FAttachmentTransformRules::KeepWorldTransform);
        AuraCapsule->SetCapsuleRadius(Effect.AuraRadius);
        //AuraEffect = Effect;
    }
}

void AAuraRadiusActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (!OtherActor) return;

    UAbilitySystemComponent* ASC = OtherActor->FindComponentByClass<UAbilitySystemComponent>();
    if (ASC)
    {

    }
}

void AAuraRadiusActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (!OtherActor) return;

    UAbilitySystemComponent* ASC = OtherActor->FindComponentByClass<UAbilitySystemComponent>();
    if (ASC)
    {

    }
}