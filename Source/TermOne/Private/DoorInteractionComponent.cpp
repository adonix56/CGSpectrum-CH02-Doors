// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorInteractionComponent.h"

// Sets default values
UDoorInteractionComponent::UDoorInteractionComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void UDoorInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	FRotator DesiredRotation(0.0f, 90.0f, 0.0f);
	GetOwner()->SetActorRotation(DesiredRotation);

}

// Called every frame
void UDoorInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}
