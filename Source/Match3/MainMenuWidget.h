// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetBase.h"
#include "MainMenuWidget.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class MATCH3_API UMainMenuWidget : public UWidgetBase
{
	GENERATED_BODY()
	
public:
	UMainMenuWidget(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(meta = ( BindWidget ))
	UButton* StartNewGameButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ConnectionNameLabel;

	UFUNCTION(BlueprintCallable)
	void OnStartNewGameClicked();

	void NativeConstruct() override;
	bool Initialize() override;
	
	void OnOpen() override;
	void OnClose() override;
};
