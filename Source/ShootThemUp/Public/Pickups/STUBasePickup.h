// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBasePickup.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUBasePickup : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ASTUBasePickup();

protected:
	/** Collision for this pickup. Character will pick this pickup when overlap that collision. */
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USphereComponent* CollisionComponent;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**
	 * Event when this actor overlaps another actor, for example a player walking into a trigger.
	 * For events when objects have a blocking collision, for example a player hitting a wall, see 'Hit' events.
	 * @note Components on both this and the other Actor must have bGenerateOverlapEvents set to true to generate overlap events.
	 */
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
