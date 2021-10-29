// Fill out your copyright notice in the Description page of Project Settings.


#include "GameController.h"
#include "InGameHUD.h"
#include "MatchController.h"
#include "ConnectionController.h"

// Sets default values for this component's properties
UGameController::UGameController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	
}

// Called when the game starts
void UGameController::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->bEnableClickEvents = true;

	InGameHUD = Cast<AInGameHUD>(PlayerController->GetHUD());
	InGameHUD->SetGameController(this);

	Match = std::make_shared<MatchController>(*this);
	Connection = std::make_shared<ConnectionController>(*this);

	Match->Begin();
	Connection->Begin();
}


void UGameController::BeginDestroy()
{
	Super::BeginDestroy();
	
	// OVO KASNIJE SKUZI STA SE DESAVA
	if(Match.get() != nullptr)
		Match->End();
	if(Connection.get() != nullptr)
		Connection->End();
}

// Called every frame
void UGameController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

