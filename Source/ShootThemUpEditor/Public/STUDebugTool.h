// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "STUDebugTool.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUPEDITOR_API ASTUDebugTool : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ASTUDebugTool();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	/** Calls ImGui::Text() and wraps it around FString type. */
	static void UnrealImGuiText(FString Text);
	
	/** Setup style for ImGui. */
	void StyleImGui();
	
};
