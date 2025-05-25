// Shoot Them Up Game. All Rights Reserved.


#include "Weapon/STUBaseWeapon.h"

#include "GameFramework/Character.h"
#include "Player/STUBaseCharacter.h"
#include "Engine/DamageEvents.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All)

// Sets default values
ASTUBaseWeapon::ASTUBaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}

void ASTUBaseWeapon::StartFire()
{
}

void ASTUBaseWeapon::StopFire()
{
}

// Called when the game starts or when spawned
void ASTUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	check(WeaponMesh)
}

void ASTUBaseWeapon::MakeDamage(const FHitResult& HitResult)
{
	AActor* DamagedActor = HitResult.GetActor();
	if (DamagedActor)
	{
		DamagedActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);
	}
}

void ASTUBaseWeapon::MakeShoot()
{
}

APlayerController* ASTUBaseWeapon::GetPlayerController() const
{
	const ACharacter* Player = Cast<ACharacter>(GetOwner());
	if (!Player) return nullptr;

	return Player->GetController<APlayerController>();
}

bool ASTUBaseWeapon::GetPlayerViewPoint(FVector& OutViewLocation, FRotator& OutViewRotation) const
{
	const APlayerController* Controller = GetPlayerController();
	if (!Controller) return false;

	Controller->GetPlayerViewPoint(OutViewLocation, OutViewRotation);

	return true;
}

FVector ASTUBaseWeapon::GetMuzzleWorldLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool ASTUBaseWeapon::GetTraceData(FVector& OutTraceStart, FVector& OutTraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

	OutTraceStart = ViewLocation;
	const FVector ShootDirection = ViewRotation.Vector();
	OutTraceEnd = OutTraceStart + ShootDirection * TraceMaxDistance;

	return true;
}

void ASTUBaseWeapon::MakeHit(FHitResult& OutHitResult, const FVector& OutTraceStart, const FVector& OutTraceEnd)
{
	if (!GetWorld()) return;
	
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	
	GetWorld()->LineTraceSingleByChannel(OutHitResult, OutTraceStart, OutTraceEnd, ECC_Visibility, CollisionParams);
}

