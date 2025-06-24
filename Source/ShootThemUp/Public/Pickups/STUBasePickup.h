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
	TObjectPtr<class USphereComponent> CollisionComponent;

	/** A time to spawn this pickup again after it was taken. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float RespawnTime = 5.0f;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**
	 * Event when this actor overlaps another actor, for example a player walking into a trigger.
	 * For events when objects have a blocking collision, for example a player hitting a wall, see 'Hit' events.
	 * @note Components on both this and the other Actor must have bGenerateOverlapEvents set to true to generate overlap events.
	 */
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	/**
	 * Event when an actor no longer overlaps another actor, and they have separated.
	 * @note Components on both this and the other Actor must have bGenerateOverlapEvents set to true to generate overlap events.
	 */
	virtual void NotifyActorEndOverlap(AActor* OtherActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	/** 
	 * Characters that are overlapping with this pickup right now.
	 * Adds an ability to be picked up on every frame.
	 */
	UPROPERTY()
	TArray<APawn*> OverlappingPawns;

	/** A yaw rotation to add every frame. */
	float RotationYaw = 0.0f;
	
	/** 
	 * Give pickup to choosen pawn.
	 * @returns True if pawn can pick this pickup and false if for example we want add health but pawn already have full health.
	 * @important Should be overriden in parent class because otherwise it will be impossible to pick it up.
	 */
	virtual bool GivePickupTo(APawn* PlayerPawn);

	/** Called when the pickup was taken. */
	void PickupWasTaken();

	/** Called after timer ended (RespawnTime). */
	void Respawn();

	/** Generate speed and direction to rotate pickup every frame. */
	void GenerateRotationYaw();

};
