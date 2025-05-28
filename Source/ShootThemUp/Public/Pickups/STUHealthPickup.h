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

protected:
	/** How much health to add when character picks this pickup. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "100.0"))
	float HealthAmount = 100.0f;
	
private:
	/**
	 * Give pickup to chosen pawn.
	 * @returns True if pawn can pick this pickup and false if for example we want to add health but pawn already have full health.
	 * @important Should be overriden in parent class because otherwise it will be impossible to pick it up.
	 */
	virtual bool GivePickupTo(APawn* PlayerPawn) override;

};
