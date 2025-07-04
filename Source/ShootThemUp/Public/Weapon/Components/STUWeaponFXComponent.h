// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUCoreTypes.h"
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
	FImpactData DefaultImpactData;

	/** Choose what effects to play on different physical materials. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	TMap<UPhysicalMaterial*, FImpactData> ImpactDataMap;

	/** Controls how far decals are rendered. If 0.0 it's always rendered. */
	UPROPERTY(EditDefaultsOnly, Category = "VFX", meta = (ClampMin = "0.0", ClampMax = "0.01"))
	float DecalsFadeDistance = 0.0f;
	
};
