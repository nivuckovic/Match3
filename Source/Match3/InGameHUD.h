// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include <map>
#include <string>
#include "WidgetBase.h"
#include "GameController.h"
#include "WidgetBase.h"

#include "InGameHUD.generated.h"


enum class GameHUDType
{
	None,
	MainMenu,
	WaitingMenu
};

UCLASS()
class MATCH3_API AInGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	AInGameHUD();
	
	virtual void DrawHUD() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	void SetGameController(UGameController* gameController);

	template <typename TClass>
	void OpenHUDWidget(const FInputModeDataBase& inputMode = FInputModeGameOnly(), bool showMouseCursor = true);
	void CloseCurrentlyOpenedWidget();

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> WaitingMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> MatchGameWidgetClass;

private:
	void MapHUDClass();
private:
	UWidgetBase* _currentlyOpenedWidget;
	bool _widgetOpened;

	bool _hudClassMapped;
	std::map<std::string, TSubclassOf<UUserWidget>> _HUDClassMap;

	UGameController* _gameController;
};

template <typename TClass>
void AInGameHUD::OpenHUDWidget(const FInputModeDataBase& inputMode, bool showMouseCursor)
{
	std::string className = typeid(TClass).name();

	CloseCurrentlyOpenedWidget();

	if (!_hudClassMapped)
	{
		MapHUDClass();
		_hudClassMapped = true;
	}

	_currentlyOpenedWidget = CreateWidget<TClass>(GetWorld(), _HUDClassMap[className]);
	_currentlyOpenedWidget->SetGameController(_gameController);
	_currentlyOpenedWidget->AddToViewport();

	_currentlyOpenedWidget->OnOpen();

	_gameController->PlayerController->SetInputMode(inputMode);
	_gameController->PlayerController->SetShowMouseCursor(showMouseCursor);

	_widgetOpened = true;
}