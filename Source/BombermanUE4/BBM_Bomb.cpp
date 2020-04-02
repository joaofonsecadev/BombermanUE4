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
	UE_LOG(LogTemp, Error, TEXT("Bomb exploding"));
	DrawDebugSphere(GetWorld(), GetActorLocation(), ExplosionRadius, 50.0f, FColor::Cyan, true, -1.0f, 0, 2.0f);
	Destroy();
}
