#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MPT_Bomb.generated.h"

UCLASS()
class MPTUT_API AMPT_Bomb : public AActor
{
	GENERATED_BODY()
	
public:	
	AMPT_Bomb();

protected:
	virtual void BeginPlay() override;
	UStaticMeshComponent* BombMesh;
	virtual void Destroyed() override;
};
