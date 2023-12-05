// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "ObjectiveComponent.h"
#include "ObjectiveHud.h"
#include "ObjectiveWorldSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class TERMONE_API UObjectiveWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	//void CreateObjectiveWidget(TSubclassOf<UObjectiveHud> ObjectiveWidgetClass);
	//void DisplayObjectiveWidget();

	//void OnMapStart() ;

	void OnObjectCompleted();

	UFUNCTION(BlueprintCallable)
	void AddObjective(UObjectiveComponent* ObjectiveComponent);

	UFUNCTION(BlueprintCallable)
	void RemoveObjective(UObjectiveComponent* ObjectiveComponent);

	UFUNCTION(BlueprintCallable)
	FString GetCurrentObjectiveDescription();

	//We call this from maps that we want to display objectives(ie main menu will not call this function)
	UFUNCTION(BlueprintCallable)
	void OnMapStart();

protected:
	virtual void Deinitialize() override;

	void CreateObjectiveWidgets();
	void DisplayObjectiveWidget();
	void RemoveObjectiveWidget();

	void DisplayObjectivesCompleteWidget();
	void RemoveObjectivesCompleteWidget();

	uint32 GetCompletedObjectiveCount();

	void OnObjectiveStateChanged(UObjectiveComponent* ObjectiveComponent, EObjectiveState ObjectiveState);
private:
	UObjectiveHud* ObjectiveWidget = nullptr;

	UUserWidget* ObjectivesCompleteWidget = nullptr;

	TArray<UObjectiveComponent*> Objectives;
};
