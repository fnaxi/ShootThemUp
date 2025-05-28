// Shoot Them Up Game. All Rights Reserved.


#include "Pickups/STUHealthPickup.h"

#include "STUUtils.h"
#include "Components/STUHealthComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All)

bool ASTUHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
	// Check is character dead
	USTUHealthComponent* HealthComponent = FSTUUtils::GetSTUPlayerComponent<USTUHealthComponent>(PlayerPawn);
	if (!HealthComponent) return false;
	
	return HealthComponent->TryToAddHealth(HealthAmount);
}

