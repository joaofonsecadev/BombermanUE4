// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "BombermanCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Bomb.h"

//////////////////////////////////////////////////////////////////////////
// ABomberCharacter

ABombermanCharacter::ABombermanCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void ABombermanCharacter::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<AGrid> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		Grid = Cast<AGrid>(*ActorItr);
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void ABombermanCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("PlaceBomb", IE_Pressed, this, &ABombermanCharacter::PlaceBomb);

	PlayerInputComponent->BindAction("MoveUp", IE_Pressed, this, &ABombermanCharacter::MoveUp);
	PlayerInputComponent->BindAction("MoveDown", IE_Pressed, this, &ABombermanCharacter::MoveDown);
	PlayerInputComponent->BindAction("MoveLeft", IE_Pressed, this, &ABombermanCharacter::MoveLeft);
	PlayerInputComponent->BindAction("MoveRight", IE_Pressed, this, &ABombermanCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	//PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	//PlayerInputComponent->BindAxis("TurnRate", this, &ABomberCharacter::TurnAtRate);
	//PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	//PlayerInputComponent->BindAxis("LookUpRate", this, &ABomberCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ABombermanCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ABombermanCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ABombermanCharacter::OnResetVR);	
}


void ABombermanCharacter::SetAmmo()
{
	Ammo++;
}

void ABombermanCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ABombermanCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void ABombermanCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void ABombermanCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABombermanCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ABombermanCharacter::MoveUp()
{
	Grid->MovePlayer(this, 0, -1);
}

void ABombermanCharacter::MoveDown()
{
	Grid->MovePlayer(this, 0, 1);
}

void ABombermanCharacter::MoveLeft()
{
	Grid->MovePlayer(this, -1, 0);
}

void ABombermanCharacter::MoveRight()
{
	Grid->MovePlayer(this, 1, 0);
}

void ABombermanCharacter::PlaceBomb()
{
	if (Ammo != 0) 
	{
		FActorSpawnParameters SpawnParams;
		if (Grid->BombGrid[PlayerX][PlayerY] != 'b') 
		{
			ABomb* SpawnedBomb = Cast<ABomb>(GetWorld()->SpawnActor<AActor>(Bomb, FVector(NextLocation.X, NextLocation.Y, NextLocation.Z - PlayerHeight), GetActorRotation(), SpawnParams));
			SpawnedBomb->BombX = PlayerX;
			SpawnedBomb->BombY = PlayerY;
			Grid->PlaceBomb(SpawnedBomb);
			Ammo--;
		}		
	}
}
