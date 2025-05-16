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
	bool IsDead() const { return FMath::IsNearlyZero(Health); }

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
	
};
