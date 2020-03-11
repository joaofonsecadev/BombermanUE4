// Fill out your copyright notice in the Description page of Project Settings.


#include "BBM_PowerUp.h"
#include "Engine/World.h"

// Sets default values
ABBM_PowerUp::ABBM_PowerUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABBM_PowerUp::BeginPlay()
{
	Super::BeginPlay();
	
	SetPowerUpType();
	SpawnPowerUp();
}

// Called every frame
void ABBM_PowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABBM_PowerUp::SetPowerUpType()
{
	int Random = FMath::FRandRange(0, 2);

	if (Random < 1)
		Type = PowerUpType::KickBombs;
	else
		Type = PowerUpType::MoreBombs;
}

void ABBM_PowerUp::SpawnPowerUp()
{
	FActorSpawnParameters SpawnParams;
	TSubclassOf<AActor> ActorToSpawn;

	switch (Type) 
	{
		case PowerUpType::KickBombs:
		ActorToSpawn = KickBombsPowerUp;
		break;
		case PowerUpType::MoreBombs:
		ActorToSpawn = MoreBombsPowerUp;
		break;
	}

	GetWorld()->SpawnActor<AActor>(ActorToSpawn, GetActorLocation(), FRotator(0.0f, 0.0f, 0.0f), SpawnParams);	
}
