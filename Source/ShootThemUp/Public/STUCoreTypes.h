// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "STUCoreTypes.generated.h"

/************************************************************************/
/*                              WEAPON                                  */
/************************************************************************/

DECLARE_MULTICAST_DELEGATE_OneParam(FOnClipEmptySignature, class ASTUBaseWeapon*)

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
	TSubclassOf<ASTUBaseWeapon> WeaponClass;

	/** Reload animation montage for this weapon. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	UAnimMontage* ReloadAnimMontage;
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct FWeaponUIData
{
	GENERATED_USTRUCT_BODY()

	/** Main icon for this weapon. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	UTexture2D* MainIcon;
	
	/** Crosshair icon for this weapon. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	UTexture2D* CrosshairIcon;
};

/************************************************************************/
/*                              HEALTH                                  */
/************************************************************************/

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature)
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, float, float);

/************************************************************************/
/*                           VISUAL EFFECTS                             */
/************************************************************************/

/**
 *
 */
USTRUCT(BlueprintType)
struct FDecalData
{
	GENERATED_USTRUCT_BODY()

	/** Material for this decal. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UMaterialInterface* Material;

	/** Size of this decal. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	FVector Size = FVector(10.0f);

	/** Life time of this decal. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	float LifeTime = 5.0f;

	/** The time of decal fade out animation. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	float FadeOutTime = 0.7f;
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FImpactData
{
	GENERATED_USTRUCT_BODY()

	/** Effect of the impact. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	class UNiagaraSystem* NiagaraEffect;

	/** Decal info for this impact. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	FDecalData DecalData;
};
