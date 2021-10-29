// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include <memory>
#include <string>

#include "GameController.generated.h"

class AInGameHUD;
class MatchController;
class ConnectionController;

class AMatchLevel;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MATCH3_API UGameController : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGameController();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	APlayerController* PlayerController;
	AInGameHUD* InGameHUD;

	std::shared_ptr<MatchController> Match;
	std::shared_ptr<ConnectionController> Connection;

	std::string ConnectionName;

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMatchLevel> MatchLevelClass;
};
