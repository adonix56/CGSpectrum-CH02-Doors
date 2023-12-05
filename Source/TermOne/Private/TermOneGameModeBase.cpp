// Fill out your copyright notice in the Description page of Project Settings.


#include "TermOneGameModeBase.h"
#include "ObjectiveWorldSubsystem.h"

void ATermOneGameModeBase::StartPlay() {
	Super::StartPlay();

	/*if (ObjectiveWidget == nullptr) {
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		ObjectiveWidget = CreateWidget<UUserWidget>(PlayerController, ObjectiveWidgetClass);
	}

	if (ObjectiveWidget) {
		ObjectiveWidget->AddToViewport();
	}
	*/

	/*
	UObjectiveWorldSubsystem* ObjectiveWorldSubsystem = GetWorld()->GetSubsystem<UObjectiveWorldSubsystem>();

	if (ObjectiveWorldSubsystem) {
		ObjectiveWorldSubsystem->CreateObjectiveWidget(ObjectiveWidgetClass);
		ObjectiveWorldSubsystem->DisplayObjectiveWidget();
	}*/
}