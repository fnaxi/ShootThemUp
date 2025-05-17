// Shoot Them Up Game. All Rights Reserved.


#include "Components/STUWeaponComponent.h"

#include "GameFramework/Character.h"
#include "Weapon/STUBaseWeapon.h"

// Sets default values for this component's properties
USTUWeaponComponent::USTUWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void USTUWeaponComponent::Fire()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->Fire();
	}
}

// Called when the game starts
void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
}

void USTUWeaponComponent::SpawnWeapon()
{
	if (!GetWorld()) return;
	
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;
	
	CurrentWeapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(WeaponClass);
	if (!CurrentWeapon) return;
	
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPointName);
}

