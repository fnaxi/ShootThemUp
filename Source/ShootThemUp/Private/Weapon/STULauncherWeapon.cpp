// Shoot Them Up Game. All Rights Reserved.


#include "Weapon/STULauncherWeapon.h"

#include "Weapon/STUProjectile.h"

void ASTULauncherWeapon::StartFire()
{
	MakeShoot();
}

void ASTULauncherWeapon::MakeShoot()
{
	if (!GetWorld() || IsAmmoEmpty()) return;
	
	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd)) return;

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();
	
	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
	ASTUProjectile* Projectile = GetWorld()->SpawnActorDeferred<ASTUProjectile>(ProjectileClass, SpawnTransform);
	if (Projectile)
	{
		Projectile->SetShootDirection(Direction);
		Projectile->SetOwner(GetOwner());
		
		Projectile->FinishSpawning(SpawnTransform);
	}

	DecreaseAmmo();
	SpawnMuzzleFX();

	PlayFireCameraShake();
}

