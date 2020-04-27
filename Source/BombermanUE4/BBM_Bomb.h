	// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BBM_Bomb.generated.h"

UCLASS()
class BOMBERMANUE4_API ABBM_Bomb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABBM_Bomb();

	UPROPERTY(EditAnywhere)
	int ExplosionRange;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> BombExplosionFX;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBombExploded);
	FBombExploded& OnExplode() { return BombExploded; }

private:

	UPROPERTY(EditAnywhere)
	float TimeToExplode;

	UFUNCTION(Server, Reliable)
	void Explode();

	FBombExploded BombExploded;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
