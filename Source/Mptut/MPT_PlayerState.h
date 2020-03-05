// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MPT_PlayerState.generated.h"

UCLASS()
class MPTUT_API AMPT_PlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	void ToggleReadyStatus();
	bool isPlayerReady = false;
};
