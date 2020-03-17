// Fill out your copyright notice in the Description page of Project Settings.


#include "BBM_Grid.h"
#include "Engine/World.h"

void UBBM_Grid::InitializeGrid(int _Width, int Height, float CellSize, TSubclassOf<AActor> FloorTile, TSubclassOf<AActor> WallTile)
{
	Width = _Width;
	Grid = new char* [Width];
	for (int i = 0; i < Width; ++i)
	{
		Grid[i] = new char[Height];
	}

	TSubclassOf<AActor> ActorToSpawn;
	FActorSpawnParameters SpawnParams;

	for (int x = 0; x < Width; x++)
	{
		for (int y = 0; y < Height; y++)
		{
			if (x == 0 || y == 0 || x == (Width - 1) || y == (Height - 1) || (x % 2 == 0 && y % 2 == 0))
				Grid[x][y] = 'w';
			else
				Grid[x][y] = 'f';

			switch (Grid[x][y])
			{
			case 'f':
				ActorToSpawn = FloorTile;
				break;
			case 'w':
				ActorToSpawn = WallTile;
				break;
			}

			GetWorld()->SpawnActor<AActor>(ActorToSpawn, FVector(0.0f + (y * CellSize * -100.0f), 0.0f + (x * CellSize * 100.0f), 0.0f), FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
		}
	}
}

void UBBM_Grid::BeginDestroy()
{
	Super::BeginDestroy();

	for (int i = 0; i < Width; ++i)
		delete[] Grid[i];
	delete[] Grid;
}
