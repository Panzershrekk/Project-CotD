#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DamageColorInfo.h"
#include "COTDDamageManager.generated.h"

class UCOTDGameInstance;

UCLASS(Blueprintable)
class PROJECTCOTD_API UCOTDDamageManager : public UObject
{
    GENERATED_BODY()

public:
    void Initialize(UCOTDGameInstance* Instance);

    UPROPERTY(BlueprintReadOnly, Category = "Color")
    UCOTDGameInstance* COTDGameInstance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    UDataTable* DamageDataTable;

    UFUNCTION(BlueprintCallable, Category = "Damage")
    FLinearColor GetColorForDamageType(FGameplayTag DamageTag) const;
    UFUNCTION(BlueprintCallable, Category = "Damage")
    float GetMultiplierFromTag(FGameplayTag DamageTag, const UAbilitySystemComponent* ASC) const;
};