// Fill out your copyright notice in the Description page of Project Settings.


#include "BBM_Wall.h"
#include "Engine/World.h"

// Sets default values
ABBM_Wall::ABBM_Wall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABBM_Wall::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABBM_Wall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABBM_Wall::DestroySelf()
{
	int32 Random = FMath::FRandRange(0, 100);
	bool bHasPowerUp = false;

	if (Random <= 30)	
		bHasPowerUp = true;

	if (bHasPowerUp) 
	{
		FActorSpawnParameters SpawnParams;
		//TSubclassOf<AActor> ActorToSpawn;		

		FVector SpawnPosition = GetActorLocation();
		GetWorld()->SpawnActor<AActor>(MoreBombsPowerUp, SpawnPosition, FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
	} 

	Destroy();
}
