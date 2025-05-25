// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()

public:
	/** Start or stop shooting. */
	virtual void StartFire() override;
	virtual void StopFire() override;

protected:
	/** Time between shots when fire button is hold. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TimeBetweenShots = 0.1f;

	/** A spread of the bullets in a cone. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float BulletSpread = 1.5f;
	
	/** Make a shoot. */
	virtual void MakeShoot() override;

	/** Get info about start and end locations of trace for shooting. */
	virtual bool GetTraceData(FVector& OutTraceStart, FVector& OutTraceEnd) const override;

private:
	/** A timer for auto-shooting when fire button is hold. */
	FTimerHandle ShootTimerHandle;

};
