// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "BombermanCharacter.h"
#include "Bomb.h"

// Sets default values
AGrid::AGrid()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGrid::BeginPlay()
{
	Super::BeginPlay();

	InitLevelGrid();
	InitPlayerGrid();
	InitBombGrid();
	GenerateLevelGrid();
	PopulateLevelGrid();
	PopulatePlayerGrid();
}

// Called every frame
void AGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Player->SetActorLocation(FMath::VInterpTo(Player->GetActorLocation(), DesiredLocation, DeltaTime, LerpSpeed));
}

void AGrid::InitLevelGrid()
{
	LevelGrid = new char* [Width];
	for (int i = 0; i < Width; ++i)
	{
		LevelGrid[i] = new char[Height];
	}
}

void AGrid::InitPlayerGrid()
{
	PlayerGrid = new char* [Width];
	for (int i = 0; i < Width; ++i)
	{
		PlayerGrid[i] = new char[Height];
	}
}

void AGrid::InitBombGrid()
{
	BombGrid = new char* [Width];
	for (int i = 0; i < Width; ++i)
	{
		BombGrid[i] = new char[Height];
	}
}

void AGrid::GenerateLevelGrid()
{
	for (int x = 0; x < Width; x++)
	{
		for (int y = 0; y < Height; y++)
		{
			if (x == 0 || y == 0 || x == (Width - 1) || y == (Height - 1))
				LevelGrid[x][y] = 'w';
			else
				LevelGrid[x][y] = 'f';
		}
	}
}

void AGrid::PopulateLevelGrid()
{
	TSubclassOf<AActor> ActorToSpawn;
	FActorSpawnParameters SpawnParams;

	for (int x = 0; x < Width; x++)
	{
		for (int y = 0; y < Height; y++)
		{
			switch (LevelGrid[x][y])
			{
			case 'f':
				ActorToSpawn = FloorTile;
				break;
			case 'w':
				ActorToSpawn = WallTile;
				break;
			case 's':
				ActorToSpawn = NULL;
				break;
			}
			
			GetWorld()->SpawnActor<AActor>(ActorToSpawn, FVector(0.0f + (y * CellSize * -100.0f), 0.0f + (x * CellSize * 100.0f), 0.0f), FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
		}
	}
}

void AGrid::PopulatePlayerGrid()
{
	for (int x = 0; x < Width; x++)
	{
		for (int y = 0; y < Height; y++)
		{
			PlayerGrid[x][y] = ' ';
		}
	}

	FActorSpawnParameters SpawnParams;
	DesiredLocation = FVector(0.0f + (PlayerSpawnPosition.Y * CellSize * -100.0f), 0.0f + (PlayerSpawnPosition.X * CellSize * 100.0f), 200.0f);
	Player = GetWorld()->SpawnActor<AActor>(PlayerCharacter, DesiredLocation, FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
	ABombermanCharacter* PlayerClass = Cast<ABombermanCharacter>(Player);
	PlayerClass->NextLocation = DesiredLocation;
	float x = PlayerSpawnPosition.X;
	float y = PlayerSpawnPosition.Y;
	PlayerGrid[(int)x][(int)y] = 'p';
	PlayerClass->PlayerX = (int)x;
	PlayerClass->PlayerY = (int)y;	
}

void AGrid::PopulateBombGrid()
{
	for (int x = 0; x < Width; x++)
	{
		for (int y = 0; y < Height; y++)
		{
			BombGrid[x][y] = ' ';
		}
	}
}

void AGrid::MovePlayer(AActor* CallingPlayer, float x, float y)
{
	bHasMoved = false;

	ABombermanCharacter* PlayerClass = Cast<ABombermanCharacter>(CallingPlayer);

	if (!bHasMoved)
	{
		int a = PlayerClass->PlayerX + x;
		int b = PlayerClass->PlayerY + y;
		if (LevelGrid[a][b] != 'w')
		{
			DesiredLocation = FVector(0.0f + (b * CellSize * -100.0f), 0.0f + (a * CellSize * 100.0f), 200.0f);
			FRotator DesiredRotation = FRotationMatrix::MakeFromX(FVector(-y, x, 0)).Rotator();
			PlayerClass->NextLocation = DesiredLocation;
			PlayerGrid[PlayerClass->PlayerX][PlayerClass->PlayerY] = ' ';
			PlayerGrid[a][b] = 'p';
			PlayerClass->PlayerX = a;
			PlayerClass->PlayerY = b;
			CallingPlayer->SetActorRotation(DesiredRotation);
			bHasMoved = true;
		}
	}
}

void AGrid::PlaceBomb(AActor* Bomb)
{
	ABomb* BombClass = Cast<ABomb>(Bomb);
	BombGrid[BombClass->BombX][BombClass->BombY] = 'b';
}

void AGrid::CheckBombCollisions(AActor* Bomb, int ExplosionRange)
{
	FActorSpawnParameters SpawnParams;

	ABomb* BombClass = Cast<ABomb>(Bomb);

	int MaxRangeDown = BombClass->BombX - ExplosionRange;
	int MaxRangeUp = BombClass->BombX + ExplosionRange;
	int MaxRangeRight = BombClass->BombY + ExplosionRange;
	int MaxRangeLeft = BombClass->BombY - ExplosionRange;

	for (int a = BombClass->BombX; a < MaxRangeUp; a++)
	{
		for (int b = BombClass->BombX - 1; b > MaxRangeDown; b--)
		{
			if (a < Height && LevelGrid[a][BombClass->BombY] == 'f')
			{
				GetWorld()->SpawnActor<AActor>(Explosion, FVector(0.0f + (BombClass->BombY * CellSize * -100.0f), 0.0f + (a * CellSize * 100.0f), 100.0f), FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
			}
			if (b > 0 && LevelGrid[b][BombClass->BombY] == 'f')
			{
				GetWorld()->SpawnActor<AActor>(Explosion, FVector(0.0f + (BombClass->BombY * CellSize * -100.0f), 0.0f + (b * CellSize * 100.0f), 100.0f), FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
			}
		}
	}

	for (int c = BombClass->BombY + 1; c < MaxRangeRight; c++)
	{
		for (int d = BombClass->BombY - 1; d > MaxRangeLeft; d--)
		{
			if (c < Width && LevelGrid[BombClass->BombX][c] == 'f')
			{
				GetWorld()->SpawnActor<AActor>(Explosion, FVector(0.0f + (c * CellSize * -100.0f), 0.0f + (BombClass->BombX * CellSize * 100.0f), 100.0f), FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
			}
			if (d > 0 && LevelGrid[BombClass->BombX][d] == 'f')
			{
				GetWorld()->SpawnActor<AActor>(Explosion, FVector(0.0f + (d * CellSize * -100.0f), 0.0f + (BombClass->BombX * CellSize * 100.0f), 100.0f), FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
			}
		}
	}

	BombGrid[BombClass->BombX][BombClass->BombY] = ' ';
}

void AGrid::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	for (int i = 0; i < Width; ++i)
		delete[] LevelGrid[i];
	delete[] LevelGrid;

	for (int i = 0; i < Width; ++i)
		delete[] PlayerGrid[i];
	delete[] PlayerGrid;

	for (int i = 0; i < Width; ++i)
		delete[] BombGrid[i];
	delete[] BombGrid;
}