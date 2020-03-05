#include "MPT_Bomb.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"

AMPT_Bomb::AMPT_Bomb()
{
	PrimaryActorTick.bCanEverTick = false;
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/PolygonPrototype/Meshes/Props/SM_Prop_Barrel_01.SM_Prop_Barrel_01'"));
	BombMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	BombMesh->SetupAttachment(RootComponent);
	BombMesh->SetStaticMesh(MeshAsset.Object);
	BombMesh->SetSimulatePhysics(true);
}

void AMPT_Bomb::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
		SetLifeSpan(5);
	}
}

void AMPT_Bomb::Destroyed()
{
	Super::Destroyed();
	UE_LOG(LogTemp, Warning, TEXT("Coisas a acontecer com o destroy"));
}