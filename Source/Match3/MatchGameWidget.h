// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WidgetBase.h"

#include "GameEventSubscription.h"
#include "GameEvents.h"

#include "MatchGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class MATCH3_API UMatchGameWidget : public UWidgetBase
{
	GENERATED_BODY()
	
public:
	void OnOpen() override;
	void OnClose() override;


	void OnUpdateCurrentTurnLabelEvent(std::shared_ptr<UpdateCurrentTurnLabelEvent> data);
	void UpdateCurrentTurnLabel();

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurrentTurnLabel;

private:
	EventSubscription::Ptr _updateCurrentTurnLabelSubscription;
};
