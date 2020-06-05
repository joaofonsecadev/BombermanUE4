#include "BBM_GameMode.h"
#include "BBM_GameState.h"
#include "BBM_Grid.h"
#include "Engine/EngineBaseTypes.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "BBM_Character.h"
#include "BBM_PlayerController.h"
#include "BBM_GameOverScreen.h"

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

	if ((ConnectedPlayers >= RequiredPlayerNumber))
	{	
		if (bPlayersHaveBeenSpawned)
		{
			int32 i = m_PControllerArray.IndexOfByKey(NewPlayer);
			SpawnLogic(i);
		}
		else
		{
			for (int8 i = 0; i < m_PControllerArray.Num(); i++)
			{
				SpawnLogic(i);
			}
			bPlayersHaveBeenSpawned = true;
		}		
	}	
}

void ABBM_GameMode::ShowGameOverScreen()
{
	for (int i = 0; i < m_PControllerArray.Num(); i++)
	{
		ABBM_Character* PCPawn = Cast<ABBM_Character>(m_PControllerArray[i]->GetPawn());
		if (PCPawn != nullptr)
		{
			if ((PCPawn->bIsDead == true) || (PCPawn->bIsDying == true))
			{
				ABBM_PlayerController* PlayerController = Cast<ABBM_PlayerController>(m_PControllerArray[i]);
				PlayerController->SpawnGameOverUI(GameOverScreen_BP);
			}
		}
	}
}

void ABBM_GameMode::SpawnLogic(int32 CurrentIndex)
{
	FTransform SpawnPlayerAt = GridManager->GetTransformFromGridReferenceCoordiantes(SpawnLocations[CurrentIndex].X, SpawnLocations[CurrentIndex].Y) + FTransform(FVector(0, 0, PlayerSpawnHeight));
	RestartPlayerAtTransform(m_PControllerArray[CurrentIndex], SpawnPlayerAt);

	ABBM_Character* Character = Cast<ABBM_Character>(m_PControllerArray[CurrentIndex]->GetCharacter());

	if (Character != nullptr)
	{
		switch (CurrentIndex + 1)
		{
		case 1:
			Character->SetColor(FLinearColor::Blue);
			break;
		case 2:
			Character->SetColor(FLinearColor::Red);
			break;
		case 3:
			Character->SetColor(FLinearColor::Green);
			break;
		case 4:
			Character->SetColor(FLinearColor::Yellow);
			break;
		}

		Character->OnPlayerDeath().AddDynamic(this, &ABBM_GameMode::ShowGameOverScreen);
	}
}

void ABBM_GameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	ConnectedPlayers--;
	m_PControllerArray.Remove(Cast<APlayerController>(Exiting));
	UE_LOG(LogTemp, Warning, TEXT("There are %d players now."), ConnectedPlayers);
}
