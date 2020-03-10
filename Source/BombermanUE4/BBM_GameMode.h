#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BBM_GameMode.generated.h"

UCLASS()
class BOMBERMANUE4_API ABBM_GameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ABBM_GameMode();

	UPROPERTY(EditDefaultsOnly)
	TArray<FVector2D> SpawnLocations;

	UPROPERTY(EditDefaultsOnly)
	int8 MaxPlayers = 2;
	int8 CurrentPlayers = 0;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> FloorTile;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> WallTile;

	UPROPERTY(EditAnywhere)
	int Height;
	UPROPERTY(EditAnywhere)
	int Width;
	UPROPERTY(EditAnywhere)
	float CellSize = 1.0f;

	char** Grid;

protected:
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer);

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

	void GenerateGrid();
};
