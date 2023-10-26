// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "ObjectiveComponent.h"
#include "ObjectiveWorldSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class TERMONE_API UObjectiveWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	void CreateObjectiveWidget(TSubclassOf<UUserWidget> ObjectiveWidgetClass);
	void DisplayObjectiveWidget();

	void OnObjectCompleted();

	UFUNCTION(BlueprintCallable)
	void AddObjective(UObjectiveComponent* ObjectiveComponent);

	UFUNCTION(BlueprintCallable)
	void RemoveObjective(UObjectiveComponent* ObjectiveComponent);

	UFUNCTION(BlueprintCallable)
	FString GetCurrentObjectiveDescription();

	void OnObjectiveStateChanged(UObjectiveComponent* ObjectiveComponent, EObjectiveState ObjectiveState);
private:
	UUserWidget* ObjectiveWidget = nullptr;

	TArray<UObjectiveComponent*> Objectives;
};
