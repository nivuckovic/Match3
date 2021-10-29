// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class GameController;

class MATCH3_API BaseController
{
public:
	BaseController(UGameController& gameController) : _gameController(gameController) {};

	virtual void Begin() = 0;
	virtual void End() = 0;

protected:
	UGameController& _gameController;
};
