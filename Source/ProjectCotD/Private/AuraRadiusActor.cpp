// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraRadiusActor.h"
#include "ControllableEntity.h"
#include "COTDGameplayAbility.h"

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

void AAuraRadiusActor::Initialize(AActor* InOwner, const UGameplayEffectAura* AE)
{
    OwnerActor = InOwner;
    if (OwnerActor && AE)
    {
        AttachToActor(OwnerActor, FAttachmentTransformRules::KeepWorldTransform);
        AuraCapsule->SetCapsuleRadius(AE->AuraRadius);
        AuraEffect = AE;
        IsIniatilized = true;

        TArray<AActor*> OverlappingActors;
        AuraCapsule->GetOverlappingActors(OverlappingActors, AControllableEntity::StaticClass());

        for (AActor* Actor : OverlappingActors)
        {
            if (Actor)
            {
                OnOverlapBegin(AuraCapsule, Actor, nullptr, 0, false, FHitResult());
            }
        }

    }
}

void AAuraRadiusActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (IsIniatilized == false || !OtherActor) return;

    UCOTDAbilitySystemComponent* ASC = OtherActor->FindComponentByClass<UCOTDAbilitySystemComponent>();
    if (ASC)
    {
        FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
        TArray<TSubclassOf<UGameplayEffect>> EffectsToApplyWithAura = AuraEffect->EffectsToApplyWithAura;
        for (TSubclassOf<UGameplayEffect> Effect : EffectsToApplyWithAura)
        {
            //UCOTDGameplayAbility::ApplyCustomGameplayEffectToTarget(ASC, Effect);
            ASC->ApplyGameplayEffectToSelf(Effect.GetDefaultObject(), 1.0f, EffectContext);
        }

        UE_LOG(LogTemp, Warning, TEXT("In aura"));
    }
}

void AAuraRadiusActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (IsIniatilized == false || !OtherActor) return;

    UCOTDAbilitySystemComponent* ASC = OtherActor->FindComponentByClass<UCOTDAbilitySystemComponent>();
    if (ASC)
    {
        TArray<TSubclassOf<UGameplayEffect>> EffectsToApplyWithAura = AuraEffect->EffectsToApplyWithAura;
        for (TSubclassOf<UGameplayEffect> Effect : EffectsToApplyWithAura)
        {
            ASC->RemoveActiveGameplayEffectBySourceEffect(Effect, ASC);
        }
        UE_LOG(LogTemp, Warning, TEXT("Out aura"));
    }
}

void AAuraRadiusActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    TArray<AActor*> OverlappingActors;
    AuraCapsule->GetOverlappingActors(OverlappingActors, AControllableEntity::StaticClass());

    for (AActor* Actor : OverlappingActors)
    {
        if (Actor)
        {
            OnOverlapEnd(AuraCapsule, Actor, nullptr, 0);
        }
    }

    OverlappingActors.Empty();
    UE_LOG(LogTemp, Warning, TEXT("Destroy aura"));
}
