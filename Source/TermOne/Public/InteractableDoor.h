// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "InteractableDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOpenDoor);

class UDoorInteractionComponent;
/**
 * 
 */
UCLASS()
class TERMONE_API AInteractableDoor : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	AInteractableDoor();
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintAssignable, Category="Door Interaction")
	FOpenDoor OnDoorOpen;

	UFUNCTION(BlueprintCallable)
	void DoorOpen();

protected:
	UFUNCTION()
	void OnInteractionSuccess();

	UPROPERTY(EditAnywhere, NoClear)
	UDoorInteractionComponent* DoorInteractionComponent;
};
