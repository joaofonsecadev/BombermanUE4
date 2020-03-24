// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BBM_Grid.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMANUE4_API UBBM_Grid : public UObject
{
	GENERATED_BODY()
	
public:
	void InitializeGrid(int Width, int Height, float CellSize, TSubclassOf<AActor> FloorTile, TSubclassOf<AActor> WallTile, TSubclassOf<AActor> DestructibleTile, TSubclassOf<AActor> PowerUpTile);
	FTransform GetTransformFromGridReferenceCoordiantes(int x, int y);

protected:
	int32 _Width;
	int32 _Height;
	char** Grid;
	TArray<AActor*> GridReference;

	virtual void BeginDestroy() override;
};