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
	
	/** Returns true if player is alive. */
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsPlayerAlive() const;
	
	/** Is player spectating or no. */
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsPlayerSpectating() const;

	/** Event on take damage. */
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnTakeDamage();

	/** Event on heal. */
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnHeal();

	virtual bool Initialize() override;

private:
	/** Subscribe to OnHealthChanged delegate. */
	UFUNCTION()
	void OnHealthChanged(float Health, float HealthDelta);

};
