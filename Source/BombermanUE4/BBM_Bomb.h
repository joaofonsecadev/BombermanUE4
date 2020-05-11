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

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

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

	UMaterialInstanceDynamic* m_DynamicMaterial;	

	void ApplyColorToMesh();

	TArray<UStaticMeshComponent*> MyMeshes;

	UPROPERTY(ReplicatedUsing = OnRep_ReplicateMesh)
	FLinearColor m_BombColor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnRep_ReplicateMesh();	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SetBombColor(FLinearColor Color);	
};
