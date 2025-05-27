// Shoot Them Up Game. All Rights Reserved.


#include "UI/STUPlayerHUDWidget.h"

#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"

float USTUPlayerHUDWidget::GetHealthPercent() const
{
	const APawn* Player = GetOwningPlayerPawn();
	if (!Player) return 0.0f;

	const USTUHealthComponent* HealthComponent = Cast<USTUHealthComponent>(Player->GetComponentByClass(USTUHealthComponent::StaticClass()));
	if (!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}

bool USTUPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& OutUIData) const
{
	const USTUWeaponComponent* WeaponComponent = GetWeaponComponent();
	if (!WeaponComponent) return false;
	
	return WeaponComponent->GetCurrentWeaponUIData(OutUIData);
}

bool USTUPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& OutAmmoData) const
{
	const USTUWeaponComponent* WeaponComponent = GetWeaponComponent();
	if (!WeaponComponent) return false;
	
	return WeaponComponent->GetCurrentWeaponAmmoData(OutAmmoData);
}

USTUWeaponComponent* USTUPlayerHUDWidget::GetWeaponComponent() const
{
	const APawn* Player = GetOwningPlayerPawn();
	if (Player)
	{
		USTUWeaponComponent* WeaponComponent = Cast<USTUWeaponComponent>(Player->GetComponentByClass(USTUWeaponComponent::StaticClass()));
		return WeaponComponent;
	}
	return nullptr;
}

