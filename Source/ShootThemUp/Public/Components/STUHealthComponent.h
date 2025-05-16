// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTUHealthComponent();
	
	/** Get character's health. */
	float GetHealth() const { return Health; }

	/** Check is character dead or no. */
	UFUNCTION(BlueprintCallable)
	bool IsDead() const { return Health <= 0; }

	/** On death event. */
	FOnDeath OnDeath;

	/** Event when health is being changed. */
	FOnHealthChanged OnHealthChanged;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/** Max possible health for the character. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float MaxHealth = 100.0f;

private:
	/** Health character have. */
	float Health = 0.0f;

	/** Handle any damage that can be taken to character. */
	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
	
};
