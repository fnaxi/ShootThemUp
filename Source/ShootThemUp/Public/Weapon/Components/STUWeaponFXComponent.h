// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUWeaponFXComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTUWeaponFXComponent();

	/** Play impact effect on hit. */
	void PlayImpactFX(const FHitResult& Hit);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/** Niagara system to spawn on impact hit. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	class UNiagaraSystem* Effect;
	
};
