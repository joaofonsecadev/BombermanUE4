// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerSphere.h"
#include "BBM_DamageTrigger.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMANUE4_API ABBM_DamageTrigger : public ATriggerSphere
{
	GENERATED_BODY()
	
public:
	ABBM_DamageTrigger();

protected:
	UFUNCTION()
	void OverlapBegin(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void OverlapEnd(AActor* OverlappedActor, AActor* OtherActor);
};
