// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "STUCoreTypes.generated.h"

/************************************************************************/
/*                              WEAPON                                  */
/************************************************************************/

DECLARE_MULTICAST_DELEGATE(FOnClipEmptySignature)

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
USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	/** The weapon class. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<class ASTUBaseWeapon> WeaponClass;

	/** Reload animation montage for this weapon. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	UAnimMontage* ReloadAnimMontage;
};

/************************************************************************/
/*                              HEALTH                                  */
/************************************************************************/

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float);
