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

protected:
	/** A collision of this projectile. */
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	class USphereComponent* CollisionComponent;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
