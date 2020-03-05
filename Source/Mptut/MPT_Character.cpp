#include "MPT_Character.h"
#include "MPT_Bomb.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"

AMPT_Character::AMPT_Character()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	MaxHealth = 100;
	CurrentHealth = MaxHealth;
}

void AMPT_Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMPT_Character::ThrowBomb);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMPT_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMPT_Character::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMPT_Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMPT_Character::LookUpAtRate);
}

void AMPT_Character::OnRep_CurrentHealth()
{
	OnHealthUpdate();
}

void AMPT_Character::OnHealthUpdate()
{
	if (HasAuthority())
	{
		FString healthLog = FString::Printf(TEXT("%s agora tem %f de vida restante"), *GetFName().ToString(), CurrentHealth);
		if (GEngine != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, healthLog);
		}
	}
}


void AMPT_Character::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMPT_Character, CurrentHealth);
}

void AMPT_Character::ThrowBomb_Implementation()
{
	if (HasAuthority())
	{
		GetWorld()->SpawnActor<AMPT_Bomb>(AMPT_Bomb::StaticClass(), GetActorLocation() + FVector(20, 20, 0), FRotator(0, 0, 0));
	}
}

void AMPT_Character::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMPT_Character::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

float AMPT_Character::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageApplied = CurrentHealth - DamageAmount;
	if (HasAuthority())
	{
		CurrentHealth = FMath::Clamp(DamageApplied, 0.f, MaxHealth);
		OnHealthUpdate();
	}
	return DamageApplied;
}

void AMPT_Character::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMPT_Character::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}
