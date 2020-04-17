// Fill out your copyright notice in the Description page of Project Settings.


#include "BBM_UI_ConnectToIP.h"
#include "Components/Button.h"

UBBM_UI_ConnectToIP::UBBM_UI_ConnectToIP(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

bool UBBM_UI_ConnectToIP::Initialize()
{
    if(Super::Initialize())
    {
        m_BtnConnect = Cast<UButton>(GetWidgetFromName(FName(TEXT("Btn_Connect"))));
        if(m_BtnConnect != nullptr) m_BtnConnect->OnClicked.AddDynamic(this, &UBBM_UI_ConnectToIP::ConnectToServerWithIP);
        return true;
    }
    return false;
}

void UBBM_UI_ConnectToIP::ConnectToServerWithIP()
{

}

void UBBM_UI_ConnectToIP::ExitCurrentScreen()
{

}