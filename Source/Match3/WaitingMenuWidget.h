// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetBase.h"
#include "JSONObjectNode.h"
#include "WaitingMenuWidget.generated.h"


class UButton;
class UTextBlock;

UCLASS()
class MATCH3_API UWaitingMenuWidget : public UWidgetBase
{
	GENERATED_BODY()

public:
	UWaitingMenuWidget(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(meta = (BindWidget))
	UButton* ReturnToMainMenuButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* WaitingLabel;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ConnectionNameLabel;

	UFUNCTION(BlueprintCallable)
	void OnReturnToMainMenuClicked();

	void NativeConstruct() override;
	bool Initialize() override;

	void OnOpen() override;
	void OnClose() override;

private:
	void OnMatchFound(JSONObjectNode::Ptr response);

private:
	ResponseEventSubscription::Ptr _matchFoundSubscription;

};
