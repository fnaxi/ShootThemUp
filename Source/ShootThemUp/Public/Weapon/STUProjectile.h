// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUProjectile.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTUProjectile();

	/** Set shoot direction to move projectile to that location. */
	void SetShootDirection(const FVector& InDirection) { ShootDirection = InDirection; };

protected:
	/** VFX component for this projectile. */
	UPROPERTY(VisibleAnywhere, Category = "VFX")
	TObjectPtr<class USTUWeaponFXComponent> WeaponFXComponent;
	
	/** A collision of this projectile. */
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	TObjectPtr<class USphereComponent> CollisionComponent;

	/** Movement component. */
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	TObjectPtr<class UProjectileMovementComponent> MovementComponent;
	
	/** Radius of damage sphere. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float DamageRadius = 200.0f;

	/** Amount of damage in center of sphere. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float DamageAmount = 50.0f;

	/** Do in all locations at sphere same damage or no. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	bool bDoFullDamage = false;

	/** Time after which this projectile will be destroyed unless it hit something. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float LifeSeconds = 5.0f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/** Direction to move projectile to. */
	FVector ShootDirection;

	/** Event called when a component hits (or is hit by) something solid. */
	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Get controller of this projectile. The owner of this projectile is a character.  */
	AController* GetController() const;
	
};
