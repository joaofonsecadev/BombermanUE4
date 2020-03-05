// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerSphere.h"
#include "MPT_DamageTrigger.generated.h"

/**
 * 
 */
UCLASS()
class MPTUT_API AMPT_DamageTrigger : public ATriggerSphere
{
	GENERATED_BODY()
	
public:
	AMPT_DamageTrigger();

protected:
	UFUNCTION()
	void OverlapBegin(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void OverlapEnd(AActor* OverlappedActor, AActor* OtherActor);
};
