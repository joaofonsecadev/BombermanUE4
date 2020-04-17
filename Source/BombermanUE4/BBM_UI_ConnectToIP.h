// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BBM_UI_ConnectToIP.generated.h"
class UButton;

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

	UFUNCTION()
	void ConnectToServerWithIP();

	UFUNCTION()
	void ExitCurrentScreen();
};
