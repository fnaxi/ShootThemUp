// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STUGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	/** The Main Draw loop for the hud. Gets called before any messaging. Should be subclassed. */
	virtual void DrawHUD() override;

	/** Player HUD widget class. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	// Calls when game starts or when spawned
	virtual void BeginPlay() override;

private:
	/** Draw the crosshair. */
	void DrawCrosshair();
	
};
