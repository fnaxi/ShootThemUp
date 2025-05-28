// Shoot Them Up Game. All Rights Reserved.


#include "Pickups/STUAmmoPickup.h"

#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"
#include "STUUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All)

bool ASTUAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
	// Check is character dead
	const USTUHealthComponent* HealthComponent = FSTUUtils::GetSTUPlayerComponent<USTUHealthComponent>(PlayerPawn);
	if (!HealthComponent || HealthComponent->IsDead()) return false;

	USTUWeaponComponent* WeaponComponent = FSTUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(PlayerPawn);
	if (!WeaponComponent) return false;

	return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}

