// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BBM_PlayerController.generated.h"
class UBBM_GameOverScreen;

/**
 * 
 */
UCLASS()
class BOMBERMANUE4_API ABBM_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(Client, Reliable)
	void SpawnGameOverUI(TSubclassOf<UBBM_GameOverScreen> GameOverScreen_BP);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	/*UFUNCTION(Server, Reliable)
	void RestartServerLevel();*/
	void ExitLevel();			

	UPROPERTY()
	UBBM_GameOverScreen* m_GameOverScreen;	
};
