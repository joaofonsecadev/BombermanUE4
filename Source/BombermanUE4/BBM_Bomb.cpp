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

		bool bIsHit = GetWorld()->SweepMultiByChannel(OutHits, ActorLocation, ActorLocation, FQuat::Identity, ECC_WorldStatic, CollisionSphere);

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

		BombExploded.Broadcast();
		Destroy();
	}	
}
