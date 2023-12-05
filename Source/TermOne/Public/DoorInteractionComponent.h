// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerBase.h"
#include "Curves/CurveFloat.h"
#include "InteractionComponent.h"
#include "DoorInteractionComponent.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOpenDoor);

class ATriggerBox;
class IConsoleVariable;

UENUM()
enum class EDoorState {
	DS_Closed = 0	UMETA(DisplayName = "Closed"),
	DS_Opening = 1	UMETA(DisplayName = "Opening"),
	DS_Open = 2		UMETA(DisplayName = "Open"),
	DS_Locked = 3	UMETA(DisplayName = "Locked"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TERMONE_API UDoorInteractionComponent : public UInteractionComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorInteractionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void InteractionStart() override;

	UFUNCTION(BlueprintCallable)
	void DoorOpen();

	void OnDoorOpen();

	UFUNCTION(BlueprintCallable)
	bool IsOpen() { return DoorState == EDoorState::DS_Open; }

	UPROPERTY(EditAnywhere)
	FRotator DesiredRotation = FRotator::ZeroRotator;

	FRotator StartRotation = FRotator::ZeroRotator;
	FRotator FinalRotation = FRotator::ZeroRotator;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	DECLARE_EVENT(FDoorInteractionComponent, FOpened)
	FOpened& OnOpened() { return OpenedEvent; }

	FOpened OpenedEvent;

	//UPROPERTY(BlueprintAssignable, Category="Door Interaction")
	//FOpenDoor OnDoorOpened;

	static void OnDebugToggled(IConsoleVariable *Var);

	void DebugDraw();

	UPROPERTY(EditAnywhere)
	float TimeToRotate = 1.0f;

	float CurrentRotationTime = 0.0f;

	UPROPERTY(EditAnywhere)
	FRuntimeFloatCurve OpenCurve;

	UPROPERTY(BlueprintReadOnly)
	EDoorState DoorState;
	//My Try
	/*UPROPERTY(EditAnywhere)
	float DistanceToOpen;

private:
	bool BoolDoorOpen;
	*/
};
