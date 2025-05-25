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

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Make a shoot. */
	virtual void MakeShoot();

	/** Get player controller that holds this weapon. */
	APlayerController* GetPlayerController() const;

	/** Get view point of character that holds this weapon. */
	bool GetPlayerViewPoint(FVector& OutViewLocation, FRotator& OutViewRotation) const;

	/** Get world location of weapon muzzle socket. */
	FVector GetMuzzleWorldLocation() const;

	/** Get info about start and end locations of trace for shooting. */
	virtual bool GetTraceData(FVector& OutTraceStart, FVector& OutTraceEnd) const;

	/** Make a hit using trace-cast. */
	void MakeHit(FHitResult& OutHitResult, const FVector& OutTraceStart, const FVector& OutTraceEnd);
	
};
