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
	// Sets default values
	ASTURifleWeapon();
	
	/** Start or stop shooting. */
	virtual void StartFire() override;
	virtual void StopFire() override;

protected:
	/** An FX component for the rifle. */
	UPROPERTY(VisibleAnywhere, Category = "VFX")
	TObjectPtr<class USTUWeaponFXComponent> WeaponFXComponent;
	
	/** Time between shots when fire button is hold. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TimeBetweenShots = 0.1f;

	/** A spread of the bullets in a cone. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float BaseBulletSpread = 1.5f;

	/** Controls a multiplier to spread when character has low health. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FVector2D LowHealthSpreadMultiplier = FVector2D(1.0f, 5.0f);
	
	/** Damage this weapon makes. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float DamageAmount = 10.0f;

	/** FX of the rifle's trace. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	class UNiagaraSystem* TraceFX;
	
	/** A FVector variable in Niagara system that means the end of the trace location. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	FString TraceTargetName = "TraceTarget";
	
	// Called when the game starts
	virtual void BeginPlay() override;
	
	/** Make a shoot. */
	virtual void MakeShoot() override;

	/** Get info about start and end locations of trace for shooting. */
	virtual bool GetTraceData(FVector& OutTraceStart, FVector& OutTraceEnd) const override;

private:
	/** A timer for auto-shooting when fire button is hold. */
	FTimerHandle ShootTimerHandle;

	/** FX niagara component for the muzzle. It's infinite so save it to be able to set visibility when start/stop firing. */
	UPROPERTY()
	class UNiagaraComponent* MuzzleFXComponent;

	/** Take damage to actor that was hit by trace. */
	void MakeDamage(const FHitResult& HitResult);

	/** Initialize muzzle FX for firing. Spawn it at muzzle location and set it's visibility to true. */
	void InitMuzzleFX();

	/** Set visibility of infinite muzzle FX. */
	void SetMuzzleFXVisibility(bool bVisible);

	/** Spawn the FX of the trace. */
	void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd);
	
};
