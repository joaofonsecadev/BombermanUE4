// Fill out your copyright notice in the Description page of Project Settings.


#include "BBM_Bomb.h"
#include "Engine/World.h"
#include "Engine.h"
#include "DrawDebugHelpers.h"
#include "BBM_DestructibleObject.h"

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

void ABBM_Bomb::Explode_Implementation()
{
	if (HasAuthority()) 
	{
		TArray<FHitResult> OutHits;
		FVector ActorLocation = GetActorLocation();
		FCollisionShape CollisionSphere = FCollisionShape::MakeSphere(ExplosionRadius);
		UWorld* World = GetWorld();
		bool bIsHit = World->SweepMultiByChannel(OutHits, ActorLocation, ActorLocation, FQuat::Identity, ECC_WorldStatic, CollisionSphere);

		if (bIsHit)
		{
			for (auto& Hit : OutHits)
			{
				if (Hit.Actor->GetClass()->ImplementsInterface(UBBM_DestructibleObject::StaticClass()))
				{
					IBBM_DestructibleObject* DestructibleObject = Cast<IBBM_DestructibleObject>(Hit.Actor);
					DestructibleObject->DestroySelf();
				}
			}
		}
		
		FActorSpawnParameters SpawnParams;
		FVector ActorPosition = GetActorLocation();
		TArray<FVector> SpawnPositions;
		SpawnPositions.Add(ActorPosition);
		for (int i = 1; i <= ExplosionRange; i++)
		{
			SpawnPositions.Add(FVector(ActorPosition.X + (100 * i), ActorPosition.Y, ActorPosition.Z));
			SpawnPositions.Add(FVector(ActorPosition.X - (100 * i), ActorPosition.Y, ActorPosition.Z));
			SpawnPositions.Add(FVector(ActorPosition.X, ActorPosition.Y + (100 * i), ActorPosition.Z));
			SpawnPositions.Add(FVector(ActorPosition.X, ActorPosition.Y - (100 * i), ActorPosition.Z));
		}

		for (int32 i = 0; i < SpawnPositions.Num(); i++)
		{
			World->SpawnActor<AActor>(BombExplosionFX, SpawnPositions[i], FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
		}		

		BombExploded.Broadcast();
		Destroy();
	}
}
