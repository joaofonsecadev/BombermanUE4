// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BBM_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMANUE4_API ABBM_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void SetupInputComponent() override;

private:
	/*UFUNCTION(Server, Reliable)
	void RestartServerLevel();*/
	void ExitLevel();
};
