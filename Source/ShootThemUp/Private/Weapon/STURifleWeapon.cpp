// Shoot Them Up Game. All Rights Reserved.


#include "Weapon/STURifleWeapon.h"

#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"
#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraComponent.h"

ASTURifleWeapon::ASTURifleWeapon()
{
	WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFXComponent");
}

void ASTURifleWeapon::StartFire()
{
	InitMuzzleFX();
	GetWorldTimerManager().SetTimer(ShootTimerHandle, this, &ASTURifleWeapon::MakeShoot, TimeBetweenShots, true);
	MakeShoot();
}

void ASTURifleWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShootTimerHandle);
	SetMuzzleFXVisibility(false);
}

void ASTURifleWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponFXComponent);
}

void ASTURifleWeapon::MakeShoot()
{
	if (!GetWorld() || IsAmmoEmpty())
	{
		StopFire();
		return;
	}

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd))
	{
		StopFire();
		return;
	}

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);
	if (HitResult.bBlockingHit)
	{
		MakeDamage(HitResult);

		// DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Magenta, false, 3.0f, 0, 3.0f);
		// DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Orange, false, 5.0f);
		WeaponFXComponent->PlayImpactFX(HitResult);
	}
	else
	{
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Magenta, false, 3.0f, 0, 3.0f);
	}

	DecreaseAmmo();
}

bool ASTURifleWeapon::GetTraceData(FVector& OutTraceStart, FVector& OutTraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

	// TODO: Make a low-health modifier to multiply BulletSpread on it, so when character has low health it's harder to shoot
	OutTraceStart = ViewLocation;
	const float HalfRad = FMath::DegreesToRadians(BulletSpread);
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
	OutTraceEnd = OutTraceStart + ShootDirection * TraceMaxDistance;

	return true;
}

void ASTURifleWeapon::MakeDamage(const FHitResult& HitResult)
{
	AActor* DamagedActor = HitResult.GetActor();
	if (DamagedActor)
	{
		DamagedActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);
	}
}

void ASTURifleWeapon::InitMuzzleFX()
{
	if (!MuzzleFXComponent)
	{
		MuzzleFXComponent = SpawnMuzzleFX();
	}
	SetMuzzleFXVisibility(true);
}

void ASTURifleWeapon::SetMuzzleFXVisibility(bool bVisible)
{
	if (MuzzleFXComponent)
	{
		MuzzleFXComponent->SetPaused(!bVisible);
		MuzzleFXComponent->SetVisibility(bVisible, true);
	}
}

