// Shoot Them Up Game. All Rights Reserved.


#include "UI/STUPlayerHUDWidget.h"

#include "STUUtils.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"

float USTUPlayerHUDWidget::GetHealthPercent() const
{
	const USTUHealthComponent* HealthComponent = FSTUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
	if (!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}

bool USTUPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& OutUIData) const
{
	const USTUWeaponComponent* WeaponComponent = FSTUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
	if (!WeaponComponent) return false;
	
	return WeaponComponent->GetCurrentWeaponUIData(OutUIData);
}

bool USTUPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& OutAmmoData) const
{
	const USTUWeaponComponent* WeaponComponent = FSTUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
	if (!WeaponComponent) return false;
	
	return WeaponComponent->GetCurrentWeaponAmmoData(OutAmmoData);
}

bool USTUPlayerHUDWidget::IsPlayerAlive() const
{
	const USTUHealthComponent* HealthComponent = FSTUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
	return HealthComponent && !HealthComponent->IsDead(); // Keep in mind that actually HealthComponent destroys when player dies
}

bool USTUPlayerHUDWidget::IsPlayerSpectating() const
{
	const APlayerController* Controller = GetOwningPlayer();
	return Controller && Controller->GetStateName() == NAME_Spectating;
}

