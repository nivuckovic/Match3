// Fill out your copyright notice in the Description page of Project Settings.


#include "AppController.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Match3/MainMenuWidget.h"

#include "EventQueue.h"
#include "GameEvents.h"
#include "InGameHUD.h"

// Sets default values
AAppController::AAppController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_gameController = CreateDefaultSubobject<UGameController>(TEXT("Game Controller"));
	_gameController->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
}

// Called when the game starts or when spawned
void AAppController::BeginPlay()
{
	Super::BeginPlay();

}

void AAppController::BeginDestroy()
{
	Super::BeginDestroy();

	EventQueue::UnsubscribeFromAll();
}

// Called every frame
void AAppController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Socket::GetInstance().CheckForPendingData();
	EventQueue::Update();
}

/*
void AAppController::SetPlayerController()
{
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
}

void AAppController::SetNewDefaultCamera()
{
	PlayerController->SetViewTarget(MainCamera);
}
*/