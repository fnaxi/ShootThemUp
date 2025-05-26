// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeapon.generated.h"

/** 
 * Structure that describes ammo data for specific weapon type.
 */
USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_USTRUCT_BODY()
	
	/** Amount of bullets in one magazine. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 Bullets;

	/** Amount of max clips that can have the weapon. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (EditCondition = "!bInfinite"))
	int32 Clips;

	/** Is this weapon have infinite ammo or no. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	bool bInfinite;
};

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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FName MuzzleSocketName = "MuzzleSocket";

	/** Max distance of trace. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float TraceMaxDistance = 1500.0f;

	/** Ammo this weapon have on character spawn. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FAmmoData DefaultAmmo{15, 10, false};

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
	
	/** Decrease ammo the weapon have after a shoot. */
	void DecreaseAmmo();

	/** Returns true if there's no ammo for this weapon (both clips and bullets in current clip). */
	bool IsAmmoEmpty() const;
	
	/** Check is current weapon's clip empty or no. */
	bool IsClipEmpty() const;

	/** Change clip in the weapon if there are clips left. */
	void ChangeClip();

	/** Log current ammo info to console. */
	void LogAmmo();

private:
	/** Ammo that is used by weapon. */
	FAmmoData CurrentAmmo;

};
