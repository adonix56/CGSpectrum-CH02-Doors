// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveWorldSubsystem.h"
#include "TermOneGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void UObjectiveWorldSubsystem::Deinitialize() {
	ObjectiveWidget = nullptr;
	ObjectivesCompleteWidget = nullptr;
}

void UObjectiveWorldSubsystem::CreateObjectiveWidgets() {
	if (ObjectiveWidget == nullptr) {
		ATermOneGameModeBase* GameMode = Cast<ATermOneGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode) {
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			ObjectiveWidget = CreateWidget<UObjectiveHud>(PlayerController, GameMode->ObjectiveWidgetClass);
			ObjectivesCompleteWidget = CreateWidget<UUserWidget>(PlayerController, GameMode->ObjectivesCompleteWidgetClass);
		}
	}
}

void UObjectiveWorldSubsystem::DisplayObjectiveWidget() {
	//ensureMsgf(ObjectiveWidget, TEXT("UOBjectiveWorldSubsystem::DisplayObjectiveWidget() ObjectiveWidget is nullptr. Be sure to call CreateObjectiveWidget() first."));
	if (ObjectiveWidget) {
		if (!ObjectiveWidget->IsInViewport()) {
			ObjectiveWidget->AddToViewport();
		}
		ObjectiveWidget->UpdateObjectiveText(GetCompletedObjectiveCount(), Objectives.Num());
	}
}

/*void UObjectiveWorldSubsystem::OnObjectCompleted() {
	DisplayObjectiveWidget();
}*/

void UObjectiveWorldSubsystem::AddObjective(UObjectiveComponent* ObjectiveComponent) {
	check(ObjectiveComponent);

	size_t PrevSize = Objectives.Num();
	Objectives.AddUnique(ObjectiveComponent);
	if (Objectives.Num() > PrevSize) {
		ObjectiveComponent->OnStateChanged().AddUObject(this, &UObjectiveWorldSubsystem::OnObjectiveStateChanged);
	}
}

void UObjectiveWorldSubsystem::RemoveObjective(UObjectiveComponent* ObjectiveComponent) {
	int32 numRemoved = ObjectiveComponent->OnStateChanged().RemoveAll(this);
	//check(numRemoved);
	Objectives.Remove(ObjectiveComponent);
}

/*void UObjectiveWorldSubsystem::CreateObjectiveWidget() {
	if (ObjectiveWidget == nullptr) {
		ATermOneGameModeBase* GameMode = Cast<ATermOneGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode) {
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			ObjectiveWidget = CreateWidget<UObjectiveHud>
		}
	}
}

void UObjectiveWorldSubsystem::DisplayObjectiveWidget() {
	if (ObjectiveWidget) {
		ObjectiveWidget->AddToViewport();
		ObjectiveWidget->UpdateObjectiveText(GetCompletedObjectiveCount(), Objectives.Num());
	}
}*/

void UObjectiveWorldSubsystem::RemoveObjectiveWidget() {
	if (ObjectiveWidget) {
		ObjectiveWidget->RemoveFromViewport();
	}
}

void UObjectiveWorldSubsystem::DisplayObjectivesCompleteWidget() {
	if (ObjectivesCompleteWidget && !ObjectivesCompleteWidget->IsInViewport()) {
		ObjectivesCompleteWidget->AddToViewport();
	}
}

void UObjectiveWorldSubsystem::RemoveObjectivesCompleteWidget() {
	if (ObjectivesCompleteWidget) {
		ObjectivesCompleteWidget->RemoveFromViewport();
	}
}

FString UObjectiveWorldSubsystem::GetCurrentObjectiveDescription() {
	if (!Objectives.IsValidIndex(0) || Objectives[0]->GetState() == EObjectiveState::OS_Inactive) {
		return TEXT("N/A");
	}

	FString RetObjective = Objectives[0]->GetDescription();
	if (Objectives[0]->GetState() == EObjectiveState::OS_Completed) {
		RetObjective += TEXT(" Completed!");
	}
	return RetObjective;
}

uint32 UObjectiveWorldSubsystem::GetCompletedObjectiveCount()
{
	uint32 ObjectivesCompleted = 0u;

	for (const UObjectiveComponent* OC : Objectives) {
		if (OC && OC->GetState() == EObjectiveState::OS_Completed) {
			ObjectivesCompleted++;
		}
	}

	return ObjectivesCompleted;
}

void UObjectiveWorldSubsystem::OnMapStart() {
	ATermOneGameModeBase* GameMode = Cast<ATermOneGameModeBase>(GetWorld()->GetAuthGameMode());

	if (GameMode) {
		CreateObjectiveWidgets();
		DisplayObjectiveWidget();
	}
}

void UObjectiveWorldSubsystem::OnObjectiveStateChanged(UObjectiveComponent* ObjectiveComponent, EObjectiveState ObjectiveState) {

	if (Objectives.Num() == 0 || !Objectives.Contains(ObjectiveComponent)) { return; }

	if (ObjectiveWidget && ObjectivesCompleteWidget) {
		if (GetCompletedObjectiveCount() == Objectives.Num()) {
			//Game Over
			//RemoveObjectiveWidget();
			DisplayObjectivesCompleteWidget();
		}
		DisplayObjectiveWidget();
	}
}