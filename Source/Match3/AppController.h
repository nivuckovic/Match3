// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include <memory>
#include "Socket.h"
#include "GameController.h"

#include "AppController.generated.h"

class AInGameHUD;

UCLASS()
class MATCH3_API AAppController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAppController();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	
private:
	// UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	// TSubclassOf<GameController> GameControllerClass;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UGameController* _gameController;

};
