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

bool USTUPlayerHUDWidget::GetWeaponUIData(FWeaponUIData& OutUIData) const
{
	const APawn* Player = GetOwningPlayerPawn();
	if (!Player) return false;

	const USTUWeaponComponent* WeaponComponent = Cast<USTUWeaponComponent>(Player->GetComponentByClass(USTUWeaponComponent::StaticClass()));
	if (!WeaponComponent) return false;

	return WeaponComponent->GetWeaponUIData(OutUIData);
}

