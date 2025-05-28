// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STUBasePickup.h"
#include "STUHealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUHealthPickup : public ASTUBasePickup
{
	GENERATED_BODY()
	
private:
	/**
	 * Give pickup to choosen pawn.
	 * @returns True if pawn can pick this pickup and false if for example we want add health but pawn already have full health.
	 * @important Should be overriden in parent class because otherwise it will be impossible to pick it up.
	 */
	virtual bool GivePickupTo(APawn* PlayerPawn) override;

};
