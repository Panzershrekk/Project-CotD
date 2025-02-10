// Fill out your copyright notice in the Description page of Project Settings.


#include "ControllableEntity.h"
#include "EntityStats.h"
#include "ControllableEntityAttributeSet.h"

// Sets default values
AControllableEntity::AControllableEntity()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    AbilitySystemComponent = CreateDefaultSubobject<UCOTDAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
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
    if (ControllableEntityAttributeSet)
    {
        float variation = ControllableEntityAttributeSet->GetInitiativeVariation();
        return ControllableEntityAttributeSet->GetInitiative() + FMath::RandRange(-variation, variation);
    }
    return 0;
}

void AControllableEntity::DataTableSetup()
{
    if (EntityStatsDataAsset)
    {
        TSubclassOf<UAttributeSet> AttributeClass = UControllableEntityAttributeSet::StaticClass();
        UDataTable* StartingTable = EntityStatsDataAsset->EntityNumericalStats;

        if (StartingTable)
        {
           
            AbilitySystemComponent->InitStats(AttributeClass, StartingTable);
            ControllableEntityAttributeSet = AbilitySystemComponent->GetSet<UControllableEntityAttributeSet>();

            if (ControllableEntityAttributeSet)
            {
                UE_LOG(LogTemp, Warning, TEXT("ControllableEntityAttributeSet correctly initialized!"));
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("ControllableEntityAttributeSet is NULL after InitStats!"));
            }
        }
    }
}

void AControllableEntity::HandleStartOfTurnEffect()
{
    FGameplayTagContainer QueryTags;
    QueryTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("Effect.OnStartTurn")));
    const FGameplayEffectQuery Query;
    Query.OwningTagQuery.MakeQuery_MatchAllTags(QueryTags);
    TArray<FActiveGameplayEffectHandle> ActiveEffectsHandle = AbilitySystemComponent->GetActiveEffects(Query);
    for (FActiveGameplayEffectHandle& ActiveEffectHandle : ActiveEffectsHandle)
    {
        const FActiveGameplayEffect* ActiveEffect = AbilitySystemComponent->GetActiveGameplayEffect(ActiveEffectHandle);
        FGameplayEffectSpec Spec = ActiveEffect->Spec;
        const UEffectOverTurn* EffectOverTurn = Cast<UEffectOverTurn>(Spec.Def);
        if (EffectOverTurn && EffectOverTurn->bTriggerCalculationAtTherStartOfEveryTurn == true)
        {
            AbilitySystemComponent->TriggerPeriodicEffect(ActiveEffectHandle);
        }
    }
}

void AControllableEntity::DecreaseTurnRemainingOnOverTurnEffect()
{
    const FGameplayEffectQuery Query;
    TArray<FActiveGameplayEffectHandle> ActiveEffectsHandle = AbilitySystemComponent->GetActiveEffects(Query);
    for (FActiveGameplayEffectHandle& ActiveEffectHandle : ActiveEffectsHandle)
    {
        const FActiveGameplayEffect* ActiveEffect = AbilitySystemComponent->GetActiveGameplayEffect(ActiveEffectHandle);
        FGameplayEffectSpec Spec = ActiveEffect->Spec;
        const UEffectOverTurn* EffectOverTurn = Cast<UEffectOverTurn>(Spec.Def);
        if (EffectOverTurn)
        {
            AbilitySystemComponent->DecreaseOverTurnEffectTurnRemaining(ActiveEffectHandle);
        }
    }
}