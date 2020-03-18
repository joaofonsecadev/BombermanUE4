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
	void InitializeGrid(int Width, int Height, float CellSize, TSubclassOf<AActor> FloorTile, TSubclassOf<AActor> WallTile);
	AActor* GetElementAtGridReferenceCoordinates(int x, int y);
	void SetElementAtGridReferenceCoordinates(int x, int y, AActor* ActorPointer);
	FTransform GetTransformFromGridReferenceCoordiantes(int x, int y);

protected:
	int Width;
	char** Grid;
	TArray<AActor*> GridReference;

	virtual void BeginDestroy() override;
};
