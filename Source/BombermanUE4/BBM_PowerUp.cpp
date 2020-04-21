// Fill out your copyright notice in the Description page of Project Settings.


#include "BBM_PowerUp.h"
#include "Components/SphereComponent.h"
#include "BBM_Character.h"

// Sets default values
ABBM_PowerUp::ABBM_PowerUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereRadius = 25.0f;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	CollisionSphere->InitSphereRadius(SphereRadius);
	CollisionSphere->SetCollisionProfileName("Trigger");

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABBM_PowerUp::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ABBM_PowerUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABBM_PowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABBM_PowerUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr && OtherActor != this) && OtherComp != nullptr) 
	{
		ABBM_Character* Player = Cast<ABBM_Character>(OtherActor);
		if (Player != nullptr) 
		{
			Player->IncreaseAmmo(); 
			Destroy();
		}
	}
}
