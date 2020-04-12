#include "BBM_GameMode.h"
#include "BBM_GameState.h"
#include "BBM_Grid.h"
#include "Engine/EngineBaseTypes.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

ABBM_GameMode::ABBM_GameMode()
{
	bStartPlayersAsSpectators = 1;
}

void ABBM_GameMode::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABBM_GameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	if (GetNetMode() != NM_DedicatedServer)
	{
		//ConnectedPlayers++;
	}
	GridManager = NewObject<UBBM_Grid>(this);
	GridManager->InitializeGrid(Width, Height, CellSize, FloorTile, FloorPlane,WallTile, DestructibleTile, PowerUpTile);
}

void ABBM_GameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
	if (ConnectedPlayers >= MaxPlayerNumber)
	{
		ErrorMessage = TEXT("max_players_reached");
	}
	else
	{
		ConnectedPlayers++;
	}
}

void ABBM_GameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	m_PControllerArray.Add(NewPlayer);
	UE_LOG(LogTemp, Warning, TEXT("Existem %d jogadores agora"), ConnectedPlayers);
	if ((ConnectedPlayers == MaxPlayerNumber))
	{
		for (int8 i = 0; i < m_PControllerArray.Num(); i++)
		{
			FTransform SpawnPlayerAt = GridManager->GetTransformFromGridReferenceCoordiantes(SpawnLocations[i].X, SpawnLocations[i].Y) + FTransform(FVector(0, 0, PlayerSpawnHeight));
			RestartPlayerAtTransform(m_PControllerArray[i], SpawnPlayerAt);
		}
	}
}

void ABBM_GameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	ConnectedPlayers--;
}
