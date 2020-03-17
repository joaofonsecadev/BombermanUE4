#include "BBM_GameMode.h"
#include "BBM_Grid.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"

ABBM_GameMode::ABBM_GameMode()
{

}

void ABBM_GameMode::BeginPlay()
{
	Super::BeginPlay();
	GridManager = NewObject<UBBM_Grid>(this);
	GridManager->InitializeGrid(Width, Height, CellSize, FloorTile, WallTile);
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

void ABBM_GameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	// If players should start as spectators, leave them in the spectator state
	if (!bStartPlayersAsSpectators && !MustSpectate(NewPlayer) && PlayerCanRestart(NewPlayer))
	{
		// Otherwise spawn their pawn immediately
		RestartPlayer(NewPlayer);
	}
}