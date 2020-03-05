// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Grid.h"
#include "BombermanCharacter.h"
#include "GameFramework/Actor.h"
#include "Bomb.generated.h"

UCLASS()
class MPTUT_API ABomb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABomb();

	UPROPERTY(EditAnywhere)
	int ExplosionRange;

	int BombX;
	int BombY;

	ABombermanCharacter* Player;
	AGrid* Grid;

private:
	UPROPERTY(EditAnywhere)
	float TimeToExplode;

	void Explode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
