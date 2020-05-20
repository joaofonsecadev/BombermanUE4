// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBM_GameOverScreen.generated.h"
class UButton;

/**
 * 
 */
UCLASS()
class BOMBERMANUE4_API UBBM_GameOverScreen : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UBBM_GameOverScreen(const FObjectInitializer& ObjectInitializer);

protected:
	virtual bool Initialize() override;

private:
	UButton* m_BtnBackToMenu;

	UPROPERTY(EditDefaultsOnly)
	FName m_MapMainMenuName = FName(TEXT("MainMenu"));

	UFUNCTION()
	void ReturnToMainMenu();
};
