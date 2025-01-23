// Fill out your copyright notice in the Description page of Project Settings.


#include "ControllableEntity.h"
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
            AbilitySystemComponent->DefaultStartingData.Empty();
            FAttributeDefaults AttributeDefaults = FAttributeDefaults();
            AttributeDefaults.Attributes = AttributeClass;
            AttributeDefaults.DefaultStartingTable = StartingTable;
            AbilitySystemComponent->DefaultStartingData.Add(AttributeDefaults);
        }
    }
}

void AControllableEntity::HandleStartOfTurnEffect()
{
    FGameplayTagContainer QueryTags;
    QueryTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("Effect.OnStartTurn")));
    //TArray<FActiveGameplayEffectHandle> ActiveDotEffect = AbilitySystemComponent->GetActiveEffectsWithAllTags(QueryTags);
    const FGameplayEffectQuery Query;
    Query.OwningTagQuery.MakeQuery_MatchAllTags(QueryTags);
    TArray<FActiveGameplayEffectHandle> ActiveDotEffect = AbilitySystemComponent->GetActiveEffects(Query);
    for (FActiveGameplayEffectHandle& DOTEffect : ActiveDotEffect)
    {
        const FActiveGameplayEffect* ActiveDOTEffect = AbilitySystemComponent->GetActiveGameplayEffect(DOTEffect);
        FGameplayEffectSpec Spec = ActiveDOTEffect->Spec;
        const UGameplayEffect* GameplayEffect = Spec.Def;

        AbilitySystemComponent->TriggerPeriodicEffect(DOTEffect);

        /*for (const FGameplayEffectExecutionDefinition& ExecutionDef : GameplayEffect->Executions)
        {
            if (ExecutionDef.CalculationClass)
            {
                UE_LOG(LogTemp, Warning, TEXT("Execution class found: %s"), *ExecutionDef.CalculationClass->GetName());
            }
        }*/
    }
}

void AControllableEntity::DecreaseTurnRemainingOnOverTurnEffect()
{
    const FGameplayEffectQuery Query;
    TArray<FActiveGameplayEffectHandle> ActiveDotEffect = AbilitySystemComponent->GetActiveEffects(Query);
    for (FActiveGameplayEffectHandle DOTEffect : ActiveDotEffect)
    {
        const FActiveGameplayEffect* ActiveDOTEffect = AbilitySystemComponent->GetActiveGameplayEffect(DOTEffect);
        FGameplayEffectSpec Spec = ActiveDOTEffect->Spec;
        const UEffectOverTurn* EffectOverTurn = Cast<UEffectOverTurn>(Spec.Def);
        UE_LOG(LogTemp, Warning, TEXT("Effect Address: %p"), EffectOverTurn);
        if (EffectOverTurn)
        {
            //AbilitySystemComponent->DecreaseOverTurnEffectTurnRemaining(DOTEffect);
        }
        bool bWasRemoved = AbilitySystemComponent->RemoveActiveGameplayEffect(DOTEffect);
        if (bWasRemoved)
        {
            UE_LOG(LogTemp, Warning, TEXT("Effect successfully removed: %s"), *DOTEffect.ToString());
            float CurrentForce = AbilitySystemComponent->GetNumericAttribute(UControllableEntityAttributeSet::GetStrenghtAttribute());
            UE_LOG(LogTemp, Warning, TEXT("Force attribute after effect removal: %f"), CurrentForce);
            AbilitySystemComponent->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag("Effect"));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to remove effect: %s"), *DOTEffect.ToString());
        }
    }
}