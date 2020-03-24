// Fill out your copyright notice in the Description page of Project Settings.


#include "BBM_Grid.h"
#include "Engine/World.h"
#include "Containers/Array.h"
#include "Math/UnrealMathUtility.h"

void UBBM_Grid::InitializeGrid(int Width, int Height, float CellSize, TSubclassOf<AActor> FloorTile, TSubclassOf<AActor> WallTile, TSubclassOf<AActor> DestructibleTile, TSubclassOf<AActor> PowerUpTile)
{
	_Width = Width;
	_Height = Height;
	Grid = new char* [_Width];
	for (int i = 0; i < _Width; ++i)
	{
		Grid[i] = new char[_Height];
	}

	TSubclassOf<AActor> ActorToSpawn;
	FActorSpawnParameters SpawnParams;


	for (int x = 0; x < _Width; x++)
	{
		for (int y = 0; y < _Height; y++)
		{
			int32 Random = FMath::FRandRange(0, 3);

			if (x == 0 || y == 0 || x == (_Width - 1) || y == (_Height - 1) || (x % 2 == 0 && y % 2 == 0))
				Grid[x][y] = 'w';
			else if (Random == 0 || (x <= 2 && y >= (_Height - 3)) || (x <= 2 && y <= 2) || (x >= (_Width - 3) && y <= 2) || (x >= (_Width - 3) && y >= (_Height - 3)))
				Grid[x][y] = 'f';
			else if (Random == 1)
				Grid[x][y] = 'd';
			else if (Random == 2)
				Grid[x][y] = 'p';
				
			switch (Grid[x][y])
			{
				case 'f':
					ActorToSpawn = FloorTile;
					break;
				case 'w':
					ActorToSpawn = WallTile;
					break;
				case 'd':
					ActorToSpawn = DestructibleTile;
					break;
				case 'p':
					ActorToSpawn = PowerUpTile;
					break;
			}

			if (GetWorld() != nullptr)
			{
				AActor* SpawnedActor;
				if (x > 0 && x < _Width - 1 && y > 0 && y < _Height - 1)
				{
					SpawnedActor = GetWorld()->SpawnActor<AActor>(FloorTile, FVector(0.0f + (y * CellSize * -100.0f), 0.0f + (x * CellSize * 100.0f), -100.0f), FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
					GridReference.Add(SpawnedActor);
				}
				if (ActorToSpawn != FloorTile) SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, FVector(0.0f + (y * CellSize * -100.0f), 0.0f + (x * CellSize * 100.0f), 0.0f), FRotator(0.0f, 0.0f, 0.0f), SpawnParams);										
			}
		}
	}
	UE_LOG(LogTemp, Error, TEXT("Grid gerada com sucesso com tamanho %d"), GridReference.Num());
}

AActor* UBBM_Grid::GetElementAtGridReferenceCoordinates(int x, int y)
{
	return GridReference[_Width * x + y];
}

void UBBM_Grid::SetElementAtGridReferenceCoordinates(int x, int y, AActor* ActorPointer)
{
	GridReference.Insert(ActorPointer, _Width * x + y);
}

FTransform UBBM_Grid::GetTransformFromGridReferenceCoordiantes(int x, int y)
{
	/*UE_LOG(LogTemp, Error, TEXT("Vamos la buscar transforms"));
	if (GridReference.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("GridReference vazia!!!!!!!!!!"));
		return FTransform(FVector(0, 0, 200));
	}*/

	return GridReference[(_Width - 2) * FMath::Clamp(x, 0, _Width - 3) + FMath::Clamp(y, 0, _Height - 3)]->GetActorTransform();
}

void UBBM_Grid::BeginDestroy()
{
	Super::BeginDestroy();

	for (int i = 0; i < _Width; ++i)
		delete[] Grid[i];
	delete[] Grid;
}
