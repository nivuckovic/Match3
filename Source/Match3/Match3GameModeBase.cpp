// Copyright Epic Games, Inc. All Rights Reserved.


#include "Match3GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Match3/MainMenuWidget.h"

void AMatch3GameModeBase::BeginPlay()
{
    CreateWidget(GetWorld(), UMainMenuWidget::StaticClass(), TEXT("Main menu widget"))->AddToViewport();
}