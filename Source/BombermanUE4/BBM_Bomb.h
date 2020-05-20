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
	UPROPERTY(EditAnywhere)
	float TimeToDetectCollisions;

	UFUNCTION(Server, Reliable)
	void Explode();

	UFUNCTION(NetMulticast, Reliable)
	void EnableCollisionsAfterSpawn();

	FBombExploded BombExploded;

	UMaterialInstanceDynamic* m_DynamicMaterial;

	void ApplyColorToBomb();

	TArray<UStaticMeshComponent*> MyMeshes;

	FLinearColor m_BombColor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(Reliable, NetMulticast)
	void SetBombColor(FLinearColor Color);	
};
