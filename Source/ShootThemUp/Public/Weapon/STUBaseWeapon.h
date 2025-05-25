// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTUBaseWeapon();

	/** Start or stop shooting. */
	virtual void StartFire();
	virtual void StopFire();

protected:
	/** The mesh of that weapon. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

	/** A socket of muzzle. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName MuzzleSocketName = "MuzzleSocket";

	/** Max distance of trace. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TraceMaxDistance = 1500.0f;

	/** Damage this weapon makes. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float DamageAmount = 10.0f;

	/** Time between shots when fire button is hold. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TimeBetweenShots = 0.1f;

	/** A spread of the bullets in a cone. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float BulletSpread = 1.5f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Take damage to actor that was hit by trace. */
	void MakeDamage(const FHitResult& HitResult);

	/** Make a shoot. */
	void MakeShoot();

	/** Get player controller that holds this weapon. */
	APlayerController* GetPlayerController() const;

	/** Get view point of character that holds this weapon. */
	bool GetPlayerViewPoint(FVector& OutViewLocation, FRotator& OutViewRotation) const;

	/** Get world location of weapon muzzle socket. */
	FVector GetMuzzleWorldLocation() const;

	/** Get info about start and end locations of trace for shooting. */
	bool GetTraceData(FVector& OutTraceStart, FVector& OutTraceEnd) const;

	/** Make a hit using trace-cast. */
	void MakeHit(FHitResult& OutHitResult, const FVector& OutTraceStart, const FVector& OutTraceEnd);

private:
	/** A timer for auto-shooting when fire button is hold. */
	FTimerHandle ShootTimerHandle;
	
};
