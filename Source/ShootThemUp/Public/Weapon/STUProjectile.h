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
	/** A collision of this projectile. */
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	class USphereComponent* CollisionComponent;

	/** Movement component. */
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	class UProjectileMovementComponent* MovementComponent;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/** Direction to move projectile to. */
	FVector ShootDirection;
	
};
