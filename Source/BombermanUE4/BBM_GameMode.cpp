#include "BBM_GameMode.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"

ABBM_GameMode::ABBM_GameMode()
{

}

void ABBM_GameMode::BeginPlay()
{
	GenerateGrid();
}

void ABBM_GameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
	if (CurrentPlayers >= MaxPlayers)
	{
		ErrorMessage = TEXT("max_players_reached");
	}
	else
	{
		CurrentPlayers += 1;
	}
}

void ABBM_GameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	UE_LOG(LogTemp, Warning, TEXT("Existem %d jogadores agora"), CurrentPlayers);
}

void ABBM_GameMode::GenerateGrid()
{
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
			if (x == 0 || y == 0 || x == (Width - 1) || y == (Height - 1) || (x%2 == 0 && y%2 == 0))
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

void ABBM_GameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	for (int i = 0; i < Width; ++i)
		delete[] Grid[i];
	delete[] Grid;
}
