// Shoot Them Up Game. All Rights Reserved.


#include "Player/STUBaseCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/STUCharacterMovementComponent.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/DamageEvents.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter, All, All)

// Sets default values
ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 80.0f);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	HealthComponent = CreateDefaultSubobject<USTUHealthComponent>("HealthComponent");
	
	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
	HealthTextComponent->SetupAttachment(GetRootComponent());
	HealthTextComponent->bOwnerNoSee = true;

	WeaponComponent = CreateDefaultSubobject<USTUWeaponComponent>("WeaponComponent");
}

// Called when the game starts or when spawned
void ASTUBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent)
	check(HealthTextComponent)
	check(GetCharacterMovement())

	OnHealthChanged(HealthComponent->GetHealth());
	HealthComponent->OnDeath.AddUObject(this, &ASTUBaseCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &ASTUBaseCharacter::OnHealthChanged);

	LandedDelegate.AddDynamic(this, &ASTUBaseCharacter::OnGroundLanded);
}

// Called every frame
void ASTUBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASTUBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent)
	check(WeaponComponent)

	// Movement
	PlayerInputComponent->BindAxis("MoveForward", this, &ASTUBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASTUBaseCharacter::MoveRight);

	// Camera
	PlayerInputComponent->BindAxis("LookUp", this, &ASTUBaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ASTUBaseCharacter::AddControllerYawInput);

	// Actions
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTUBaseCharacter::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTUBaseCharacter::StartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTUBaseCharacter::StopRunning);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &USTUWeaponComponent::Fire);
}

bool ASTUBaseCharacter::IsRunning() const
{
	return bWantsToRun && bIsMovingForward && !GetVelocity().IsZero();
}

float ASTUBaseCharacter::GetMovementDirection() const
{
	if (GetVelocity().IsZero()) return 0.0f;
	
	typedef UE::Math::TVector<double> FVectorDouble;
	
	const FVectorDouble VelocityNormal = GetVelocity().GetSafeNormal();
	
	const double AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const FVectorDouble CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);

	const double Degrees = FMath::RadiansToDegrees(AngleBetween);
	
	return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void ASTUBaseCharacter::MoveForward(float Amount)
{
	bIsMovingForward = Amount > 0.0f;
	
	if (Amount == 0.0f) return;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ASTUBaseCharacter::MoveRight(float Amount)
{
	if (Amount == 0.0f) return;
	AddMovementInput(GetActorRightVector(), Amount);
}

void ASTUBaseCharacter::StartRunning()
{
	bWantsToRun = true;
}

void ASTUBaseCharacter::StopRunning()
{
	bWantsToRun = false;
}

void ASTUBaseCharacter::OnDeath()
{
	UE_LOG(LogBaseCharacter, Display, TEXT("Player %s is dead"), *GetName())

	PlayAnimMontage(DeathAnimMontage);
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(LifeSpanOnDeath);

	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
}

void ASTUBaseCharacter::OnHealthChanged(float Health)
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

void ASTUBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
	const double FallVelocityZ = -GetVelocity().Z;
	UE_LOG(LogBaseCharacter, Display, TEXT("FallVelocityZ: %f"), FallVelocityZ);

	if (FallVelocityZ < LandedDamageVelocity.X) return;

	const double FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
	
	UE_LOG(LogBaseCharacter, Display, TEXT("Fall Damage: %f"), FallVelocityZ);
	TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}

