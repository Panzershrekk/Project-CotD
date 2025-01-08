#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DamageColorInfo.h"
#include "DamageColorManager.generated.h"

class UCOTDGameInstance;

UCLASS(Blueprintable)
class PROJECTCOTD_API UDamageColorManager : public UObject
{
    GENERATED_BODY()

public:
    void Initialize(UCOTDGameInstance* Instance);

    UPROPERTY(BlueprintReadOnly, Category = "Color")
    UCOTDGameInstance* COTDGameInstance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    UDataTable* DamageColorDataTable;

    UFUNCTION(BlueprintCallable, Category = "Damage")
    FLinearColor GetColorForDamageType(ESubDamagerType SubDamageType) const;
};