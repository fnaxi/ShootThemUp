// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STUBasePickup.h"
#include "STUAmmoPickup.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUAmmoPickup : public ASTUBasePickup
{
	GENERATED_BODY()

protected:

	/** How many clips to add when character picks this pickup. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "10.0"))
	int32 ClipsAmount = 10;

	/** To what weapon this pickup should add clips. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	TSubclassOf<class ASTUBaseWeapon> WeaponType;

private:
	/**
	 * Give pickup to choosen pawn.
	 * @returns True if pawn can pick this pickup and false if for example we want add health but pawn already have full health.
	 * @important Should be overriden in parent class because otherwise it will be impossible to pick it up.
	 */
	virtual bool GivePickupTo(APawn* PlayerPawn) override;

};
