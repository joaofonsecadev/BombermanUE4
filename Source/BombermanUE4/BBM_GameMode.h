#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BBM_GameMode.generated.h"
class UBBM_Grid;
class UBBM_GameOverScreen;

UCLASS()
class BOMBERMANUE4_API ABBM_GameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ABBM_GameMode();

	UPROPERTY(EditDefaultsOnly)
	int8 MaxPlayerNumber = 4;

	UPROPERTY(EditDefaultsOnly)
	int8 RequiredPlayerNumber = 2;

	int8 ConnectedPlayers = 0;

	bool bPlayersHaveBeenSpawned = false;
	
	UPROPERTY(EditAnywhere, Category="References")
	TSubclassOf<AActor> FloorTile;
	UPROPERTY(EditAnywhere, Category = "References")
	TSubclassOf<AActor> FloorPlane;
	UPROPERTY(EditAnywhere, Category = "References")
	TSubclassOf<AActor> WallTile;
	UPROPERTY(EditAnywhere, Category = "References")
	TSubclassOf<AActor> InsideWallsTile;
	UPROPERTY(EditAnywhere, Category = "References")
	TSubclassOf<ACameraActor> CoolCameraClass;

	UPROPERTY(EditDefaultsOnly, Category = "Grid Settings")
	TArray<FVector2D> SpawnLocations;
	UPROPERTY(EditAnywhere, Category="Grid Settings")
	int32 Height = 11;
	UPROPERTY(EditAnywhere, Category = "Grid Settings")
	int32 Width = 11;
	UPROPERTY(EditAnywhere, Category = "Grid Settings")
	float CellSize = 1.0f;
	UPROPERTY(EditAnywhere, Category = "Grid Settings")
	float PlayerSpawnHeight = 300.0f;

	UPROPERTY()
	UBBM_Grid* GridManager;	

	virtual void Logout(AController* Exiting) override;

protected:
	virtual void InitGame(const FString & MapName, const FString & Options, FString & ErrorMessage) override;
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	//void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer);

private:
	TArray<APlayerController*> m_PControllerArray;
	TEnumAsByte<ENetMode> NetModeEnum;

	UPROPERTY(EditDefaultsOnly, Category = "References")
	TSubclassOf<UBBM_GameOverScreen> GameOverScreen_BP;

	UFUNCTION()
	void ShowGameOverScreen();

	void SpawnLogic(int32 CurrentIndex);
};
