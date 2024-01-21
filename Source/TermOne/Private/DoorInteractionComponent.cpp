// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorInteractionComponent.h"
#include "TermOnePlayerCharacter.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Engine/TriggerBox.h"
#include "Components/AudioComponent.h"
#include "ObjectiveWorldSubsystem.h"

//#include "DrawDebugHelpers.h"

constexpr float FLT_METERS(float meters) {
	return meters * 100.0f;
}

static TAutoConsoleVariable<bool> CVarToggleDebugDoor(
	TEXT("TermOne.DoorInteractionComponent.Debug"),
	false,
	TEXT("Toggle DoorInteractionComponent debug display."),
	ECVF_Default
);

// Sets default values for this component's properties
UDoorInteractionComponent::UDoorInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	CVarToggleDebugDoor.AsVariable()->SetOnChangedCallback(FConsoleVariableDelegate::CreateStatic(&UDoorInteractionComponent::OnDebugToggled));

	DoorState = EDoorState::DS_Closed;
	// ...
}

void UDoorInteractionComponent::InteractionStart() {
	Super::InteractionStart();
	UE_LOG(LogTemp, Warning, TEXT("InDoorInteraction"));
	if (InteractingActor) {
		ATermOnePlayerCharacter* PlayerCharacter = Cast<ATermOnePlayerCharacter>(InteractingActor);
		if (PlayerCharacter) {
			PlayerCharacter->DoorOpenInteractionStarted(GetOwner());
		}
	}
}


// Called when the game starts
void UDoorInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	StartRotation = GetOwner()->GetActorRotation();
	FinalRotation = GetOwner()->GetActorRotation() + DesiredRotation;
	CurrentRotationTime = 0.0f;

	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();

	if (!AudioComponent) {
		UE_LOG(LogTemp, Warning, TEXT("UDoorInteractionComponent::BeginPlay() Missing Audio Component"));
	}
	//UE_LOG(LogTemp, Warning, TEXT("Hello! YEEESH"));

	/*UObjectiveWorldSubsystem* ObjectiveWorldSubsystem = GetWorld()->GetSubsystem<UObjectiveWorldSubsystem>();

	if (ObjectiveWorldSubsystem) {
		OpenedEvent.AddUObject(ObjectiveWorldSubsystem, &UObjectiveWorldSubsystem::OnObjectCompleted);
	}
	*/
	//BoolDoorOpen = false;
	// ...
	
}

void UDoorInteractionComponent::DoorOpen() {
	if (IsOpen() || DoorState == EDoorState::DS_Opening) { return; }

	if (AudioComponent) {
		AudioComponent->Play();
	}

	DoorState = EDoorState::DS_Opening;
	CurrentRotationTime = 0.0f;
}


// Called every frame
void UDoorInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/*float CurrentDistance = FVector::Distance(GetOwner()->GetActorLocation(), GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());

	UE_LOG(LogTemp, Warning, TEXT("Distance to Door %f"), CurrentDistance);

	if (CurrentDistance < DistanceToOpen) {
		BoolDoorOpen = true;
	}*/

	/*if (DoorState == EDoorState::DS_Closed) {
		//Get Player Pawn
		APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
		//Check is Player Pawn is inside Trigger Box
		if (PlayerPawn && TriggerActor->IsOverlappingActor(PlayerPawn)) {
			DoorState = EDoorState::DS_Opening;
			CurrentRotationTime = 0.0f;
		}
	}
	else */
	if (DoorState == EDoorState::DS_Opening) {
		CurrentRotationTime += DeltaTime;
		const float TimeRatio = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);
		const float RotationAlpha = OpenCurve.GetRichCurveConst()->Eval(TimeRatio);
		const FRotator CurrentRotation = FMath::Lerp(StartRotation, FinalRotation, RotationAlpha);
		GetOwner()->SetActorRotation(CurrentRotation);

		if (TimeRatio >= 1.0f) {
			OnDoorOpen();
		}
	}

	/*if (CurrentRotationTime < TimeToRotate) {
		if (TriggerBox && GetWorld() && GetWorld()->GetFirstLocalPlayerFromController()) {
			APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

			if (PlayerPawn && TriggerBox->IsOverlappingActor(PlayerPawn)) {
				CurrentRotationTime += DeltaTime;
				const float TimeRatio = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);
				const float RotationAlpha = OpenCurve.GetRichCurveConst()->Eval(TimeRatio);
				const FRotator CurrentRotation = FMath::Lerp(StartRotation, FinalRotation, RotationAlpha);
				GetOwner()->SetActorRotation(CurrentRotation);
			}
		}
	}
	*/
	DebugDraw();
}

void UDoorInteractionComponent::OnDebugToggled(IConsoleVariable *Var) {
	UE_LOG(LogTemp, Warning, TEXT("OnDebugToggled Called"));  
}

void UDoorInteractionComponent::DebugDraw() {
	if (CVarToggleDebugDoor->GetBool()) {
		FVector Offset(FLT_METERS(-0.75f), 0.0f, FLT_METERS(2.5f));
		FVector StartLocation = GetOwner()->GetActorLocation() + Offset;
		FString EnumAsString = TEXT("Door State: ") + UEnum::GetDisplayValueAsText(DoorState).ToString();
		DrawDebugString(GetWorld(), Offset, EnumAsString, GetOwner(), FColor::Blue, 0.0f);
	}
}

void UDoorInteractionComponent::OnDoorOpen() {
	DoorState = EDoorState::DS_Open;
	UObjectiveComponent* ObjectiveComponent = GetOwner()->FindComponentByClass<UObjectiveComponent>();
	if (ObjectiveComponent) {
		ObjectiveComponent->SetState(EObjectiveState::OS_Completed);
	}
	GEngine->AddOnScreenDebugMessage(3, 3.0f, FColor::Yellow, TEXT("DoorOpened"));
	//OpenedEvent.Broadcast();
	//OnDoorOpened.Broadcast();
	InteractionSuccess.Broadcast();
}

