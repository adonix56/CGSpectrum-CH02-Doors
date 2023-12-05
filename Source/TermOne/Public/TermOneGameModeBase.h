// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "ObjectiveHud.h"
#include "TermOneGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TERMONE_API ATermOneGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void StartPlay() override;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UObjectiveHud> ObjectiveWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> ObjectivesCompleteWidgetClass;

	//UUserWidget* ObjectiveWidget = nullptr;

};
