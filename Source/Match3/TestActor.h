// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "GameEventSubscription.h"
#include "ResponseEventSubscription.h"
#include "GameEvents.h"

#include "JSONObjectNode.h"

#include "TestActor.generated.h"

UCLASS()
class MATCH3_API ATestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void AddedToQueueCallback(JSONObjectNode::Ptr responseData);
	void StartedNewGameCallback(JSONObjectNode::Ptr responseData);

	EventSubscription::Ptr _subscription;
	ResponseEventSubscription::Ptr _responseSubscription;
};
