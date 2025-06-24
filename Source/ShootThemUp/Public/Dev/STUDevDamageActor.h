// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUDevDamageActor.generated.h"

/**
 * A sphere that should imitate grenade damage for development purposes. 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUDevDamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTUDevDamageActor();

	/** Root component. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USceneComponent> SceneComponent;

	/** The radius of sphere. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius = 300.0f;

	/** The color of sphere. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor SphereColor = FColor::Red;

	/** Damage to take when character is in the sphere. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 10.0f;

	/**
	 * If true at any place in the sphere will be the same damage, otherwise in center will be
	 * the maximum damage and when going to corners it will decrease.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDoFullDamage = false;

	/** Damage type to use. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UDamageType> DamageType;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
