// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBM_UI_ConnectToIP.generated.h"
class UButton;
class UTextBlock;
class UEditableTextBox;

/**
 * 
 */
UCLASS()
class BOMBERMANUE4_API UBBM_UI_ConnectToIP : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UBBM_UI_ConnectToIP(const FObjectInitializer& ObjectInitializer);

protected:
	virtual bool Initialize() override;

private:
	UButton* m_BtnConnect;
	UTextBlock* m_TxtBtnConnect;
	UEditableTextBox* m_ETxtInputIP;
	bool bIsConnecting = false;

	UPROPERTY(EditDefaultsOnly)
	FName m_MapMainMenuName = FName(TEXT("MainMenu"));

	UFUNCTION()
	void ConnectToServerWithIP();
};
