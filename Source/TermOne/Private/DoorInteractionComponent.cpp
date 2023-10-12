// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorInteractionComponent.h"

// Sets default values for this component's properties
UDoorInteractionComponent::UDoorInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	DesiredRotation = FRotator(0.0f, 90.0f, 0.0f);
	DeltaRotation = DesiredRotation - GetOwner()->GetActorRotation();
	FinalRotation = GetOwner()->GetActorRotation() + DeltaRotation;
	//BoolDoorOpen = false;
	// ...
	
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

	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	//if (BoolDoorOpen && !CurrentRotation.Equals(FinalRotation, 5.0f)) {
	if (!CurrentRotation.Equals(FinalRotation)) {
		CurrentRotation += DeltaRotation * DeltaTime;
		GetOwner()->SetActorRotation(CurrentRotation);
	}

	// ...
}

