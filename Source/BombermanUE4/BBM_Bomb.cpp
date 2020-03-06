// Fill out your copyright notice in the Description page of Project Settings.


#include "BBM_Bomb.h"
#include "Engine/World.h"
#include "Engine.h"
#include "DrawDebugHelpers.h"

// Sets default values
ABBM_Bomb::ABBM_Bomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABBM_Bomb::BeginPlay()
{
	Super::BeginPlay();		

	for (TActorIterator<ABBM_Character> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		Player = Cast<ABBM_Character>(*ActorItr);		
	}
	for (TActorIterator<ABBM_Grid> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		Grid = Cast<ABBM_Grid>(*ActorItr);
	}

	FTimerHandle handle;
	GetWorld()->GetTimerManager().SetTimer(handle, this, &ABBM_Bomb::Explode, TimeToExplode, false);
}

// Called every frame
void ABBM_Bomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ABBM_Bomb::Explode()
{
	Grid->CheckBombCollisions(this, ExplosionRange);
	Destroy();
	Player->SetAmmo();
}
