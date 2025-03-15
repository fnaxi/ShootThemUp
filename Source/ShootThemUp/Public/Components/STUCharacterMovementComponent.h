// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "STUCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	/** A modifier when character is running. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "1.5", ClampMax = "10.0"))
	float RunModifier = 2.0f;
	
	//BEGIN UMovementComponent Interface
	virtual float GetMaxSpeed() const override;
	//END UMovementComponent Interface
	
};
