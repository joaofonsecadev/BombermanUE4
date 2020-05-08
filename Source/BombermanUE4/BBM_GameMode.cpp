#include "BBM_GameMode.h"
#include "BBM_GameState.h"
#include "BBM_Grid.h"
#include "Engine/EngineBaseTypes.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "BBM_Character.h"

ABBM_GameMode::ABBM_GameMode()
{
	bStartPlayersAsSpectators = 1;
}

void ABBM_GameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	GridManager = NewObject<UBBM_Grid>(this);
	GridManager->InitializeGrid(Width, Height, CellSize, FloorTile, FloorPlane,WallTile, InsideWallsTile, CoolCameraClass);
}

void ABBM_GameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
	if (ConnectedPlayers >= MaxPlayerNumber) ErrorMessage = TEXT("max_players_reached");
}

void ABBM_GameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	ConnectedPlayers++;
	m_PControllerArray.Add(NewPlayer);	
	UE_LOG(LogTemp, Warning, TEXT("There are %d players now."), ConnectedPlayers);	

	if ((ConnectedPlayers == MaxPlayerNumber))
	{		
		for (int8 i = 0; i < m_PControllerArray.Num(); i++)
		{
			FTransform SpawnPlayerAt = GridManager->GetTransformFromGridReferenceCoordiantes(SpawnLocations[i].X, SpawnLocations[i].Y) + FTransform(FVector(0, 0, PlayerSpawnHeight));
			RestartPlayerAtTransform(m_PControllerArray[i], SpawnPlayerAt);

			ABBM_Character* Character = Cast<ABBM_Character>(m_PControllerArray[i]->GetCharacter());

			if (Character != nullptr)
			{
				switch (i + 1)
				{
				case 1:
					Character->SetColor(FLinearColor::Blue);
					break;
				case 2:
					Character->SetColor(FLinearColor::Red);
					break;
				}
			}
		}		
	}	
}

void ABBM_GameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	ConnectedPlayers--;
	m_PControllerArray.Remove(Cast<APlayerController>(Exiting));
	UE_LOG(LogTemp, Warning, TEXT("There are %d players now."), ConnectedPlayers);
}
