// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomb.h"
#include "Engine/World.h"
#include "Engine.h"
#include "DrawDebugHelpers.h"

// Sets default values
ABomb::ABomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();		

	for (TActorIterator<ABombermanCharacter> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		Player = Cast<ABombermanCharacter>(*ActorItr);		
	}
	for (TActorIterator<AGrid> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		Grid = Cast<AGrid>(*ActorItr);
	}

	FTimerHandle handle;
	GetWorld()->GetTimerManager().SetTimer(handle, this, &ABomb::Explode, TimeToExplode, false);
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ABomb::Explode()
{
	Grid->CheckBombCollisions(this, ExplosionRange);
	Destroy();
	Player->SetAmmo();
}
