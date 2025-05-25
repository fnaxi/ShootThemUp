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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	/** Weapon to spawn. */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<class ASTUBaseWeapon> WeaponClass;

	/** Socket to attach weapon to. */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponAttachPointName = "WeaponSocket";
	
private:
	/** Current weapon character have. */
	UPROPERTY()
	ASTUBaseWeapon* CurrentWeapon = nullptr;
	
	/** Spawn weapon and attach it to socket character's mesh have. */
	void SpawnWeapon();
	
};
