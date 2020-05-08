// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBM_UI_MainMenu.generated.h"
class UButton;

/**
 * 
 */
UCLASS()
class BOMBERMANUE4_API UBBM_UI_MainMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UBBM_UI_MainMenu(const FObjectInitializer& ObjectInitializer);

protected:
	virtual bool Initialize() override;

private:
	//UButton* m_BtnHostMatch;
	UButton* m_BtnExitGame;
	UButton* m_BtnJoinMatch;
	UUserWidget* ConnectToIP;

	UPROPERTY(EditDefaultsOnly, Category="References")
	TSubclassOf<UUserWidget> ConnectToIP_BP;

	UFUNCTION()
	void ExitGame();

	UFUNCTION()
	void ShowConnectToIPUI();
};
