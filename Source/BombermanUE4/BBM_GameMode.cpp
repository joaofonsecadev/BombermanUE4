#include "BBM_GameMode.h"
#include "UObject/ConstructorHelpers.h"

ABBM_GameMode::ABBM_GameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/BombermanUE4/Blueprints/BP_Character.BP_Character"));
	DefaultPawnClass = PlayerPawnBPClass.Class;
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
