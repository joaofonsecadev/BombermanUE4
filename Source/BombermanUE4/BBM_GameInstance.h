// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BBM_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMANUE4_API UBBM_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void PostInitProperties() override;
	virtual void BeginDestroy() override;
	virtual void HandleNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString);
};
