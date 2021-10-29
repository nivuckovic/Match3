// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum class RequestType
{
	StartNewGame = 1,
	CancelStartNewGame = 2,
	TileMove = 3,
	GenerateNewTiles = 4,
	EndTurn = 5
};
