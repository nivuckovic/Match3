// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetBase.generated.h"

class GameController;

UCLASS()
class MATCH3_API UWidgetBase : public UUserWidget
{
	GENERATED_BODY()
public:
	UWidgetBase(const FObjectInitializer& ObjectInitializer);

	void SetGameController(UGameController* gameController);

	virtual void OnOpen() {};
	virtual void OnClose() {};

protected:
	UGameController* _gameController;

private:
	
};
