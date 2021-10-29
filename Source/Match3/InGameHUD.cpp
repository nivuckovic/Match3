// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameHUD.h"

#include <string>

#include "MainMenuWidget.h"
#include "WaitingMenuWidget.h"
#include "MatchGameWidget.h"

AInGameHUD::AInGameHUD()
{
}

void AInGameHUD::BeginPlay()
{
    Super::BeginPlay();

}

void AInGameHUD::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}


void AInGameHUD::SetGameController(UGameController* gameController)
{
    _gameController = gameController;
}

void AInGameHUD::CloseCurrentlyOpenedWidget()
{
	if (_widgetOpened)
	{
		_currentlyOpenedWidget->OnClose();
		_currentlyOpenedWidget->RemoveFromParent();

		_widgetOpened = false;
	}
}

void AInGameHUD::DrawHUD()
{
    Super::DrawHUD();
}

void AInGameHUD::MapHUDClass()
{
    _HUDClassMap[typeid(UMainMenuWidget).name()] = MainMenuWidgetClass;
    _HUDClassMap[typeid(UWaitingMenuWidget).name()] = WaitingMenuWidgetClass;
	_HUDClassMap[typeid(UMatchGameWidget).name()] = MatchGameWidgetClass;
}
