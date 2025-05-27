// Shoot Them Up Game. All Rights Reserved.


#include "UI/STUPlayerHUDWidget.h"

#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"

float USTUPlayerHUDWidget::GetHealthPercent() const
{
	const USTUHealthComponent* HealthComponent = GetHealthComponent();
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

bool USTUPlayerHUDWidget::IsPlayerAlive() const
{
	const USTUHealthComponent* HealthComponent = GetHealthComponent();
	return HealthComponent && !HealthComponent->IsDead(); // Keep in mind that actually HealthComponent destroys when player dies
}

bool USTUPlayerHUDWidget::IsPlayerSpectating() const
{
	const APlayerController* Controller = GetOwningPlayer();
	return Controller && Controller->GetStateName() == NAME_Spectating;
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

USTUHealthComponent* USTUPlayerHUDWidget::GetHealthComponent() const
{
	const APawn* Player = GetOwningPlayerPawn();
	if (Player)
	{
		USTUHealthComponent* HealthComponent = Cast<USTUHealthComponent>(Player->GetComponentByClass(USTUHealthComponent::StaticClass()));
		return HealthComponent;
	}
	return nullptr;
}

