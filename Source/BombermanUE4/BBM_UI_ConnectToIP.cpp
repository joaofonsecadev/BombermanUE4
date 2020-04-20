// Fill out your copyright notice in the Description page of Project Settings.


#include "BBM_UI_ConnectToIP.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetTextLibrary.h"

UBBM_UI_ConnectToIP::UBBM_UI_ConnectToIP(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

bool UBBM_UI_ConnectToIP::Initialize()
{
    if(Super::Initialize())
    {
        m_BtnConnect = Cast<UButton>(GetWidgetFromName(FName(TEXT("Btn_Connect"))));
        m_TxtBtnConnect = Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("Txt_BtnConnect"))));
        m_ETxtInputIP = Cast<UEditableTextBox>(GetWidgetFromName(FName(TEXT("ETxt_InputIP"))));

        if (m_BtnConnect != nullptr) m_BtnConnect->OnClicked.AddDynamic(this, &UBBM_UI_ConnectToIP::ConnectToServerWithIP);
        if (m_TxtBtnConnect != nullptr) m_TxtBtnConnect->SetText(FText::FromString(TEXT("Connect")));
        if (m_ETxtInputIP != nullptr) m_ETxtInputIP->SetText(FText::FromString(TEXT("0.0.0.0")));

        return true;
    }
    return false;
}

void UBBM_UI_ConnectToIP::ConnectToServerWithIP()
{
    if (!bIsConnecting)
    {
        bIsConnecting = true;

        FString IPToConnect = m_ETxtInputIP->GetText().ToString();
        GetOwningPlayer()->ClientTravel(IPToConnect, ETravelType::TRAVEL_Absolute, false);

        FString ConnectingText = "Connecting to " + IPToConnect + " ...";
        m_ETxtInputIP->SetText(FText::FromString(ConnectingText));
        m_TxtBtnConnect->SetText(FText::FromString("Cancel"));
    }
    else
    {
        UGameplayStatics::OpenLevel(GetWorld(), m_MapMainMenuName);
    }
}