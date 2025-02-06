#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "COTDAbilitySystemComponent.generated.h"

class AAuraRadiusActor;
class UCOTDGameplayAbility;

/**
 * 
 */
UCLASS()
class PROJECTCOTD_API UCOTDAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditDefaultsOnly, Category = "Aura")
    TSubclassOf<AAuraRadiusActor> AuraActorClass;

    TMap<FActiveGameplayEffectHandle, TWeakObjectPtr<AAuraRadiusActor>> ActiveAuraEffects;

    //Custom function to trigger calculation function on periodic effect
    void TriggerPeriodicEffect(FActiveGameplayEffectHandle Handle)
    {
        //ActiveGameplayEffects.ExecutePeriodicGameplayEffect(Handle);
    }

    const FActiveGameplayEffectsContainer& GetActiveGameplayEffectsContainer() const
    {
        return ActiveGameplayEffects;
    }

    UFUNCTION(BlueprintCallable, Category = "GAS")
    void DecreaseOverTurnEffectTurnRemaining(FActiveGameplayEffectHandle& EffectHandle);

    UFUNCTION(BlueprintCallable, Category = "GAS")

    float GetSetByCallerMagnitudeFromEffect(FActiveGameplayEffectHandle EffectHandle, FGameplayTag CallerTag) const
    {
        if (const FActiveGameplayEffect* ActiveEffect = GetActiveGameplayEffect(EffectHandle))
        {
            return ActiveEffect->Spec.GetSetByCallerMagnitude(CallerTag, false);
        }

        return -1.0f;
    }

    UFUNCTION(BlueprintCallable, Category = "GAS")
    void ApplyCustomGameplayEffectToTarget(UCOTDGameplayAbility* GA, UCOTDAbilitySystemComponent* Target, TSubclassOf<UGameplayEffect> EffectClass, float EffectLevel);
    void OnEffectRemoved(const FActiveGameplayEffect& RemovedEffect);
    void Test()
    {
        for (int32 i = 0; i < DefaultStartingData.Num(); ++i)
        {
            UE_LOG(LogTemp, Warning, TEXT("Looping on DefaultStartingData"));
            if (DefaultStartingData[i].Attributes && DefaultStartingData[i].DefaultStartingTable)
            {
                UAttributeSet* Attributes = const_cast<UAttributeSet*>(GetOrCreateAttributeSubobject(DefaultStartingData[i].Attributes));
                //Attributes->InitFromMetaDataTable(DefaultStartingData[i].DefaultStartingTable);
                const UDataTable* DataTable = DefaultStartingData[i].DefaultStartingTable;
                static const FString Context = FString(TEXT("UAttribute::BindToMetaDataTable"));

                for (TFieldIterator<FProperty> It(GetClass(), EFieldIteratorFlags::IncludeSuper); It; ++It)
                {
                    FProperty* Property = *It;
                    FNumericProperty* NumericProperty = CastField<FNumericProperty>(Property);
                    if (NumericProperty)
                    {
                        FString RowNameStr = FString::Printf(TEXT("%s.%s"), *Property->GetOwnerVariant().GetName(), *Property->GetName());
                        UE_LOG(LogTemp, Warning, TEXT("Numeric propty: %s"), *FString(RowNameStr));

                        FAttributeMetaData* MetaData = DataTable->FindRow<FAttributeMetaData>(FName(*RowNameStr), Context, false);
                        if (MetaData)
                        {
                            void* Data = NumericProperty->ContainerPtrToValuePtr<void>(this);
                            NumericProperty->SetFloatingPointPropertyValue(Data, MetaData->BaseValue);
                        }
                    }
                    else if (FGameplayAttribute::IsGameplayAttributeDataProperty(Property))
                    {
                        FString RowNameStr = FString::Printf(TEXT("%s.%s"), *Property->GetOwnerVariant().GetName(), *Property->GetName());
                        UE_LOG(LogTemp, Warning, TEXT("No Numeric propty: %s"), *FString(RowNameStr));

                        FAttributeMetaData* MetaData = DataTable->FindRow<FAttributeMetaData>(FName(*RowNameStr), Context, false);
                        if (MetaData)
                        {
                            FStructProperty* StructProperty = CastField<FStructProperty>(Property);
                            check(StructProperty);
                            FGameplayAttributeData* DataPtr = StructProperty->ContainerPtrToValuePtr<FGameplayAttributeData>(this);
                            check(DataPtr);
                            DataPtr->SetBaseValue(MetaData->BaseValue);
                            DataPtr->SetCurrentValue(MetaData->BaseValue);
                        }
                    }
                }
                UE_LOG(LogTemp, Warning, TEXT("Initing data"));

            }
        }
    }
};
