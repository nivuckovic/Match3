// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum class ResponseType
{
	AddedToQueue = 1,
	StartedNewGame = 2,
	NewConnection = 4,
	OpponentMoveTile = 5,
	NewTilesGenerated = 8,
	EndTurn = 9
};