#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BBM_GameMode.generated.h"
class UBBM_Grid;

UCLASS()
class BOMBERMANUE4_API ABBM_GameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ABBM_GameMode();

	UPROPERTY(EditDefaultsOnly)
	int8 MaxPlayers = 2;
	int8 CurrentPlayers = 0;
	
	UPROPERTY(EditAnywhere, Category="References")
	TSubclassOf<AActor> FloorTile;
	UPROPERTY(EditAnywhere, Category = "References")
	TSubclassOf<AActor> WallTile;

	UPROPERTY(EditDefaultsOnly, Category = "Grid Settings")
	TArray<FVector2D> SpawnLocations;
	UPROPERTY(EditAnywhere, Category="Grid Settings")
	int32 Height = 11;
	UPROPERTY(EditAnywhere, Category = "Grid Settings")
	int32 Width = 11;
	UPROPERTY(EditAnywhere, Category = "Grid Settings")
	float CellSize = 1.0f;

	UPROPERTY()
	UBBM_Grid* GridManager;

protected:
	virtual void InitGame(const FString & MapName, const FString & Options, FString & ErrorMessage) override;
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer);
	virtual void BeginPlay() override;

private:
	int8 SpawnedNumber = 0;
};
