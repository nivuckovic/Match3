// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetBase.h"

#include "GameController.h"

UWidgetBase::UWidgetBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UWidgetBase::SetGameController(UGameController* gameController)
{
	_gameController = gameController;
}