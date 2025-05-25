// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
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
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	/** Weapons to spawn for the character. */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<TSubclassOf<class ASTUBaseWeapon>> WeaponClasses;

	/** Socket to attach weapon to equip. */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";
	
	/** Socket to attach weapon to armory. */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";
	
	/** Animation montage to play when equipping new weapon. */
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* EquipAnimMontage;
	
private:
	/** Current weapon character have. */
	UPROPERTY()
	ASTUBaseWeapon* CurrentWeapon = nullptr;

	/** Weapons the character have. */
	UPROPERTY()
	TArray<ASTUBaseWeapon*> Weapons;

	/** An index of weapon that is current one now. */
	int32 CurrentWeaponIndex = 0;

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
	
};
