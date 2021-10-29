// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActor.h"

#include <functional>
#include "EventQueue.h"
#include <string>
#include "GameEvents.h"
#include "Grid.h"

#include "UObject/ConstructorHelpers.h"

// Sets default values
ATestActor::ATestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FString testactor = ATestActor::StaticClass()->GetFullName();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *testactor);

	FString gridactor = AGrid::StaticClass()->GetFullName();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *gridactor);


}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();
	
	// std::function<void(std::shared_ptr<TestGE>)> func = std::bind(&ATestActor::Test, this, std::placeholders::_1);
    // _subscription = EventQueue::SubscribeToEvent<TestGE>(func);

	// EventQueue::CallEvent(std::make_shared<StartNewGameEvent>(std::bind(&ATestActor::AddedToQueueCallback, this, std::placeholders::_1)));

	// EventQueue::SubscribeToResponseEvent(ResponseType::StartedNewGame, std::bind(&ATestActor::StartedNewGameCallback, this, std::placeholders::_1));
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATestActor::StartedNewGameCallback(JSONObjectNode::Ptr responseData)
{
	FString temp(responseData->ToString().c_str());
	UE_LOG(LogTemp, Warning, TEXT("StartedNewGame! %s"), *temp);
}

void ATestActor::AddedToQueueCallback(JSONObjectNode::Ptr responseData)
{
	FString temp(responseData->ToString().c_str());
	UE_LOG(LogTemp, Warning, TEXT("AddedToQueue! %s"), *temp);
}

