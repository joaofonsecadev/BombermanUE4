// Fill out your copyright notice in the Description page of Project Settings.


#include "BBM_Grid.h"
#include "Engine/World.h"
#include "Containers/Array.h"
#include "Math/UnrealMathUtility.h"
#include "Components/StaticMeshComponent.h"

void UBBM_Grid::InitializeGrid(int Width, int Height, float CellSize, TSubclassOf<AActor> FloorTile, TSubclassOf<AActor> FloorPlane, TSubclassOf<AActor> WallTile, TSubclassOf<AActor> InsideWallsTile)
{
	_Width = Width;
	_Height = Height;
	Grid = new int8* [_Width];
	for (int i = 0; i < _Width; ++i)
	{
		Grid[i] = new int8[_Height];
	}

	TSubclassOf<AActor> ActorToSpawn;
	FActorSpawnParameters SpawnParams;

	UWorld* World = GetWorld();
	for (int x = 0; x < _Width; x++)
	{
		for (int y = 0; y < _Height; y++)
		{
			int32 Random = FMath::FRandRange(0, 2);

			if (x == 0 || y == 0 || x == (_Width - 1) || y == (_Height - 1) || (x % 2 == 0 && y % 2 == 0))
			{
				Grid[x][y] = Wall;
				ActorToSpawn = WallTile;
			}
			else if (Random == 0 || (x <= 2 && y >= (_Height - 3)) || (x <= 2 && y <= 2) || (x >= (_Width - 3) && y <= 2) || (x >= (_Width - 3) && y >= (_Height - 3)))
			{
				Grid[x][y] = Floor;
				ActorToSpawn = FloorTile;
			}
			else if (Random == 1)
			{
				Grid[x][y] = InsideWalls;
				ActorToSpawn = InsideWallsTile;
			}
			if (World != nullptr)
			{
				AActor* SpawnedActor;
				//Spawning floor tiles and adding each one to GridReference
				if (x > 0 && x < _Width - 1 && y > 0 && y < _Height - 1)
				{
					SpawnedActor = World->SpawnActor<AActor>(FloorTile, FVector(0.0f + (y * CellSize * -100.0f), 0.0f + (x * CellSize * 100.0f), -100.0f), FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
					FloorActorCoordinates.Add(SpawnedActor);
				}
				if (ActorToSpawn != FloorTile) SpawnedActor = World->SpawnActor<AActor>(ActorToSpawn, FVector(0.0f + (y * CellSize * -100.0f), 0.0f + (x * CellSize * 100.0f), 0.0f), FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
			}
		}
	}
	
	FVector GridCenter = GetGridCenterLocation() + FVector(0.0f, 0.0f, 100.0f);
	AActor* SpawnedFloor = World->SpawnActor<AActor>(FloorPlane, GridCenter, FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
	SpawnedFloor->SetActorScale3D(FVector(_Height, _Width, 1));
	SpawnedFloor->SetActorLocation(GridCenter);
}

FTransform UBBM_Grid::GetTransformFromGridReferenceCoordiantes(int x, int y)
{
	return FloorActorCoordinates[(_Width - 2) * FMath::Clamp(x, 0, _Width - 3) + FMath::Clamp(y, 0, _Height - 3)]->GetActorTransform();
}

FVector UBBM_Grid::GetGridCenterLocation()
{
	int32 IndexToSearchFor = (FloorActorCoordinates.Num() / 2);
	FTransform GridCenterTransform = FloorActorCoordinates[IndexToSearchFor]->GetActorTransform();
	return GridCenterTransform.GetLocation();
}

void UBBM_Grid::BeginDestroy()
{
	Super::BeginDestroy();
	for (int i = 0; i < _Width; ++i)
		delete[] Grid[i];
	delete[] Grid;
}
