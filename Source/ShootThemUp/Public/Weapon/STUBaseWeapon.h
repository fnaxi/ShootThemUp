// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUCoreTypes.h"
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

	/** Broadcast when clip in the weapon is empty. */
	FOnClipEmptySignature OnClipEmpty;

	/** Start or stop shooting. */
	virtual void StartFire();
	virtual void StopFire();

	/** Change clip in the weapon if there are clips left. */
	void ChangeClip();

	/** Can reload this weapon or no. */
	bool CanReload() const;

	/** Get UI data for this weapon. */
	FWeaponUIData GetUIData() const { return UIData; }

	/** Get current ammo. */
	FAmmoData GetAmmoData() const { return CurrentAmmo; }

	/** Add clips amount to this weapon if ammo is not full. */
	bool TryToAddAmmo(int32 ClipsAmount);

	/** Check is this weapon firing now or not. */
	bool IsFiring() const;

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

	/** UI data for this weapon. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FWeaponUIData UIData;
	
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

	/** Checks is ammo full or no. */
	bool IsAmmoFull() const;

	/** Check is current weapon's clip empty or no. */
	bool IsClipEmpty() const;

	/** Log current ammo info to console. */
	void LogAmmo();

	/** Is this weapon fires now or no. */
	bool bFireInProgress = false;

private:
	/** Ammo that is used by weapon. */
	FAmmoData CurrentAmmo;

};
