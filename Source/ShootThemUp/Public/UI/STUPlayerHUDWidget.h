// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUCoreTypes.h"
#include "Blueprint/UserWidget.h"
#include "STUPlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/** Get percent of the character health. */
	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthPercent() const;

	/** Get UI data of current weapon character have. */
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetCurrentWeaponUIData(FWeaponUIData& OutUIData) const;
	
	/** Get ammo data of current weapon character have. */
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetCurrentWeaponAmmoData(FAmmoData& OutAmmoData) const;

private:
	/** Get weapon component from owning this UI character. */
	class USTUWeaponComponent* GetWeaponComponent() const;
	
};
