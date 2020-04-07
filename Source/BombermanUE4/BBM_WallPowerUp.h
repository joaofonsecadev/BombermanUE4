// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BBM_DestructibleObject.h"
#include "BBM_WallPowerUp.generated.h"

UENUM()
enum class PowerUpType : uint8
{
	MoreBombs,
	KickBombs
};

UCLASS()
class BOMBERMANUE4_API ABBM_WallPowerUp : public AActor, public IBBM_DestructibleObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABBM_WallPowerUp();
	
	virtual void DestroySelf() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> KickBombsPowerUp;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> MoreBombsPowerUp;

	UPROPERTY(VisibleAnywhere)
	PowerUpType Type;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetPowerUpType();
	void SpawnPowerUp();

};
