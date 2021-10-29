// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"

#include "Components/Button.h"
#include "GameController.h"
#include "InGameHUD.h"
#include "WaitingMenuWidget.h"
#include "Components/TextBlock.h"


UMainMenuWidget::UMainMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UMainMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();


}

bool UMainMenuWidget::Initialize()
{
    Super::Initialize();

	// StartNewGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnStartNewGameClicked);

    return true;
}

void UMainMenuWidget::OnStartNewGameClicked()
{
    _gameController->InGameHUD->OpenHUDWidget<UWaitingMenuWidget>(FInputModeUIOnly(), true);
}

void UMainMenuWidget::OnOpen()
{
    FString connectionName(("Connection: " + _gameController->ConnectionName).c_str());
    ConnectionNameLabel->SetText(FText::FromString(connectionName));
}

void UMainMenuWidget::OnClose()
{

}
