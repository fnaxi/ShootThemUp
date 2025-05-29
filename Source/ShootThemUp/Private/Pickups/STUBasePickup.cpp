// Shoot Them Up Game. All Rights Reserved.


#include "Pickups/STUBasePickup.h"

#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All)

// Sets default values
ASTUBasePickup::ASTUBasePickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->InitSphereRadius(50.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	SetRootComponent(CollisionComponent);
}

// Called when the game starts or when spawned
void ASTUBasePickup::BeginPlay()
{
	Super::BeginPlay();

	check(CollisionComponent);
	GenerateRotationYaw();
}

void ASTUBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	APawn* Pawn = Cast<APawn>(OtherActor);
	if (GivePickupTo(Pawn))
	{
		PickupWasTaken();
	}
	else if (Pawn)
	{
		OverlappingPawns.Add(Pawn);
	}
}

void ASTUBasePickup::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	APawn* Pawn = Cast<APawn>(OtherActor);
	OverlappingPawns.Remove(Pawn);
}

// Called every frame
void ASTUBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0.0f, RotationYaw * DeltaTime, 0.0f));

	for (APawn* OverlapPawn : OverlappingPawns)
	{
		if (GivePickupTo(OverlapPawn))
		{
			PickupWasTaken();
			break;
		}
	}
}

bool ASTUBasePickup::GivePickupTo(APawn* PlayerPawn)
{
	return false;
}

void ASTUBasePickup::PickupWasTaken()
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(false, true);
	}

	// Respawn this pickup
	FTimerHandle RespawnTimerHandle;
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASTUBasePickup::Respawn, RespawnTime);
}

void ASTUBasePickup::Respawn()
{
	GenerateRotationYaw();
	
	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(true, true);
	}
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
}

void ASTUBasePickup::GenerateRotationYaw()
{
	const float Direction = FMath::RandBool() ? 1.0f : -1.0f;
	RotationYaw = FMath::RandRange(100.0f, 150.0f) * Direction;
}

