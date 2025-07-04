// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUBaseCharacter.generated.h"

/**
 * Provides shared functionality such as movement, health management,
 * animations, and weapon handling for both player-controlled and AI-controlled characters.
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
	TObjectPtr<class UCameraComponent> CameraComponent;

	/** Component that holds camera. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class USpringArmComponent> SpringArmComponent;

	/** Health realization for the character. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class USTUHealthComponent> HealthComp;

	/** Weapon management and logic realization for the character. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class USTUWeaponComponent> WeaponComp;

	/** A component that renders a health above the head. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UTextRenderComponent> HealthTextComponent;

	/** Animation to play when character dies. */
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> DeathAnimMontage;
	
	/** Time to destroy character mesh. */
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float LifeSpanOnDeath = 5.0f;
	
	/** A velocity when character will get damage. */
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);

	/** What damage will get character after falling basing on LandedDamageVelocity. */
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FVector2D LandedDamage = FVector2D(10.0f, 100.0f);

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

	/** Calls USTUWeaponComponent::StartFire() but also disables ability to shoot while running. */
	void OnStartFire();
	
	/** Is character running currently or not. */
	bool bWantsToRun = false;

	/** Is character moving forward. */
	bool bIsMovingForward = false;

	/** Calls when character died. */
	void OnDeath();

	/** Calls when health is changed. */
	void OnHealthChanged(float Health, float HealthDelta);

	/** Called upon landing after falling. */
	UFUNCTION()
	void OnGroundLanded(const FHitResult& Hit);
	
};
