// Fill out your copyright notice in the Description page of Project Settings.


#include "TermOnePlayerCharacter.h"

// Sets default values
ATermOnePlayerCharacter::ATermOnePlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATermOnePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATermOnePlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATermOnePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATermOnePlayerCharacter::FellOutOfWorld(const UDamageType& dmgType) {
	APlayerController* PlayerController = GetController<APlayerController>();
	if (PlayerController) {
		PlayerController->RestartLevel();
	}
}