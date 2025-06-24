// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "STUCoreTypes.h"
#include "Components/ActorComponent.h"
#include "Pickups/STUHealthPickup.h"
#include "STUHealthComponent.generated.h"

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
	UFUNCTION(BlueprintCallable, Category = "Health")
	bool IsDead() const { return FMath::IsNearlyZero(Health); }
	
	/** Get percent of health character have. */
	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthPercent() const { return Health / MaxHealth; }

	/** Add health of it's not max, otherwise return false. */
	bool TryToAddHealth(float HealthAmount);

	/** Is health full or no. */
	float IsHealthFull() const;

	/** On death event. */
	FOnDeathSignature OnDeath;

	/** Event when health is being changed. */
	FOnHealthChangedSignature OnHealthChanged;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/** Max possible health for the character. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float MaxHealth = 100.0f;

	/** Turn auto heal on or no. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
	bool bAutoHeal = true;

	/** Frequency of healing. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "bAutoHeal"))
	float HealUpdateTime = 1.0f;

	/** With what time start healing character after taking damage. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "bAutoHeal"))
	float HealDelay = 3.0f;

	/** Character healing amount. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "bAutoHeal"))
	float HealModifier = 5.0f;

	/** Camera shake to play on damage. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	TSubclassOf<class UCameraShakeBase> CameraShake;

private:
	/** Set new character's health, ensure it's not bigger than MaxHealth and broadcast OnHealthChanged delegate. */
	void SetHealth(float NewHealth);
	
	/** Health character have. */
	float Health = 0.0f;

	/** Timer to heal character. */
	FTimerHandle HealTimerHandle;
	
	/** Calls in HealTimerHandle to heal character. */
	void HealUpdate();
	
	/** Handle any damage that can be taken to character. */
	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
	
	/** Play damage camera shake. */
	void PlayCameraShake();

};
