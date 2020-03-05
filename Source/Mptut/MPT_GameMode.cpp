#include "MPT_GameMode.h"
#include "MPT_Character.h"
#include "MPT_GameState.h"
#include "MPT_PlayerState.h"
#include "MPT_PlayerController.h"
#include "UObject/ConstructorHelpers.h"

AMPT_GameMode::AMPT_GameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	DefaultPawnClass = PlayerPawnBPClass.Class;
	GameStateClass = AMPT_GameState::StaticClass();
	PlayerStateClass = AMPT_PlayerState::StaticClass();
	PlayerControllerClass = AMPT_PlayerController::StaticClass();
}

void AMPT_GameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
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

void AMPT_GameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	UE_LOG(LogTemp, Warning, TEXT("Existem %d jogadores agora"), CurrentPlayers);
}
