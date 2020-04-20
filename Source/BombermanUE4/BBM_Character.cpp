// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "BBM_Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine.h"
#include "Engine/World.h"

ABBM_Character::ABBM_Character()
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
	CameraBoom->TargetArmLength = 0;
	CameraBoom->TargetOffset = FVector(-300, 0, 1000);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void ABBM_Character::DestroySelf()
{
	FString DeathLog = FString::Printf(TEXT("You have died.\nBut since this is a prototype, nothing happens."));
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, DeathLog);
	//Destroy();
}

void ABBM_Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("PlaceBomb", IE_Released, this, &ABBM_Character::PlaceBomb);
	PlayerInputComponent->BindAction("RestartLevel", IE_Released, this, &ABBM_Character::RestartLevel);
	PlayerInputComponent->BindAction("ExitLevel", IE_Released, this, &ABBM_Character::ExitLevel);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABBM_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABBM_Character::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ABBM_Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ABBM_Character::LookUpAtRate);
}

void ABBM_Character::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABBM_Character::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ABBM_Character::ExitLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
}

void ABBM_Character::RestartLevel_Implementation()
{
	if (HasAuthority())
	{
		UWorld* World = GetWorld();
		if (World != nullptr)
		{
			World->ServerTravel("/Game/BombermanUE4/Maps/Main");
		}
	}
}

void ABBM_Character::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ABBM_Character::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ABBM_Character::PlaceBomb_Implementation()
{
	if (HasAuthority()) 
	{
		FHitResult* HitResult = new FHitResult();
		FVector StartTrace = GetCapsuleComponent()->RelativeLocation;
		FVector DownVector = GetActorUpVector() * -1;
		FVector EndTrace = (DownVector * 5000.0f) + StartTrace;
		FCollisionQueryParams* TraceParams = new FCollisionQueryParams();

		FActorSpawnParameters SpawnParams;

		if (GetWorld()->LineTraceSingleByChannel(*HitResult, StartTrace, EndTrace, ECC_Visibility, *TraceParams))
		{
			if (HitResult->Actor->ActorHasTag("FloorTile") && Ammo > 0)
			{
				FVector TileLocation = HitResult->Actor->GetActorLocation();
				FVector SpawnPosition = FVector(TileLocation.X, TileLocation.Y, 0.0f);
				AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(Bomb, SpawnPosition, FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
				ABBM_Bomb* SpawnedBomb = Cast<ABBM_Bomb>(SpawnedActor);
				Ammo--;
				SpawnedBomb->OnExplode().AddDynamic(this, &ABBM_Character::IncreaseAmmo);
			}
		}
	}	
}

void ABBM_Character::IncreaseAmmo()
{
	Ammo++;
}
