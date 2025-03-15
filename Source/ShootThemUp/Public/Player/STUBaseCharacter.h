// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUBaseCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASTUBaseCharacter(const FObjectInitializer& ObjInit);

protected:
	/** Third-person camera for this character. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UCameraComponent* CameraComponent;

	/** Spring arm component for camera. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class USpringArmComponent* SpringArmComponent;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Getter for animation blueprint. */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsRunning() const;

	/** Get direction of movement to use right animations in blueprint. */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetMovementDirection() const;
	
private:
	/** Move forward or backward. */
	void MoveForward(float Amount);

	/** Move right or left. */
	void MoveRight(float Amount);

	/** Calls when character wants to run. */
	void StartRunning();

	/** Calls when character stopped to run. */
	void StopRunning();
	
	/** Is character running currently or not. */
	bool bWantsToRun = false;

	/** Is character moving forward. */
	bool bIsMovingForward = false;
	
};
