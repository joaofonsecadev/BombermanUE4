// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grid.generated.h"

UCLASS()
class MPTUT_API AGrid : public AActor
{
	GENERATED_BODY()	

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> FloorTile;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> WallTile;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> PlayerCharacter;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> Explosion;
	
	UPROPERTY(EditAnywhere)
	FVector2D PlayerSpawnPosition;

	UPROPERTY(EditAnywhere)
	int Width = 10;
	UPROPERTY(EditAnywhere)
	int Height = 10;
	UPROPERTY(EditAnywhere)
	float CellSize = 1.0f;

	UPROPERTY(EditAnywhere)
	float LerpSpeed = 10.0f;

	char** LevelGrid;
	char** PlayerGrid;
	char** BombGrid;

	AActor* Player = nullptr;
	FVector DesiredLocation;

	bool bHasMoved = false;	
	
	UFUNCTION(BlueprintCallable)
	void MovePlayer(AActor* CallingPlayer, float x, float y);
	UFUNCTION(BlueprintCallable)
	void PlaceBomb(AActor* Bomb);
	UFUNCTION(BlueprintCallable)
	void CheckBombCollisions(AActor* Bomb, int ExplosionRange);

	// Sets default values for this actor's properties
	AGrid();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void InitLevelGrid();
	void InitPlayerGrid();
	void InitBombGrid();
	void GenerateLevelGrid();
	void PopulateLevelGrid();
	void PopulatePlayerGrid();
	void PopulateBombGrid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
};
