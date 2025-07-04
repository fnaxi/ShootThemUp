// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUCoreTypes.h"
#include "Components/ActorComponent.h"
#include "STUWeaponComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTUWeaponComponent();

	/** Start or stop shooting. */
	void StartFire();
	void StopFire();

	/** Equip next weapon. */
	void NextWeapon();

	/**
	 * Input-callback for reloading weapon by character.
	 * @see ChangeClip()
	 */
	void Reload();

	/**
	 * Get UI/ammo data for current weapon.
	 * @returns True if current weapon is not nullptr.
	 */
	bool GetCurrentWeaponUIData(FWeaponUIData& OutUIData) const;
	bool GetCurrentWeaponAmmoData(FAmmoData& OutAmmoData) const;
	
	/** Add clips amount to chosen weapon if possible, returns false if no. */
	bool TryToAddAmmo(TSubclassOf<ASTUBaseWeapon> WeaponType, int32 ClipsAmount);
	
	/** Checks is current weapon fires now or no. */
	bool IsFiring() const;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Calls when game ends
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	/** Weapons to spawn for the character. */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<FWeaponData> WeaponData;

	/** Socket to attach weapon to equip. */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";
	
	/** Socket to attach weapon to armory. */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";
	
	/** Animation montage to play when equipping new weapon. */
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> EquipAnimMontage;
	
private:
	/** Current weapon character have. */
	UPROPERTY()
	TObjectPtr<ASTUBaseWeapon> CurrentWeapon;

	/** Weapons the character have. */
	UPROPERTY()
	TArray<TObjectPtr<ASTUBaseWeapon>> Weapons;

	/** Reload animation montage to use with currently equipped weapon. */
	UPROPERTY()
	TObjectPtr<UAnimMontage> CurrentReloadAnimMontage;

	/** An index of weapon that is current one now. */
	int32 CurrentWeaponIndex = 0;

	/** Is equip animation montage is in progress or no. */
	bool bEquipAnimInProgress = false;

	/** Is reload animation montage is in progress or no. */
	bool bReloadAnimInProgress = false;

	/** Attach weapon to one of the sockets character's mesh have. */
	void AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);

	/** Spawn weapon and attach it to socket character's mesh have. */
	void SpawnWeapons();

	/** Equip weapon of set index. */
	void EquipWeapon(int32 WeaponIndex);

	/** Play animation montage on character. */
	void PlayAnimMontage(UAnimMontage* Animation);

	/** Initialize animations for the character. */
	void InitAnimations();

	/** Called when equip animation montage was finished. */
	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);

	/** Called when reload animation montage was finished. */
	void OnReloadFinished(USkeletalMeshComponent* MeshComponent);

	/** Return true if character can shoot right now. */
	bool CanFire() const;

	/** Can equip new weapon or no. */
	bool CanEquip() const;

	/** Can reload current weapon or no. */
	bool CanReload() const;

	/** Callback for OnEmptyClip event in ASTUBaseWeapon class. Basically this implements auto-reload feature. */
	void OnClipEmpty(ASTUBaseWeapon* AmmoEmptyWeapon);

	/** Change clip in the current weapon. */
	void ChangeClip();
	
};
