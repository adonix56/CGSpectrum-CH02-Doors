// Fill out your copyright notice in the Description page of Project Settings.


#include "FireDamageActor.h"
#include "DealDamageComponent.h"
#include "TermOnePlayerCharacter.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/CapsuleComponent.h"

class ATermOnePlayerCharacter;

// Sets default values
AFireDamageActor::AFireDamageActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	//if (PlayerPawn) {
	//	UE_LOG(LogTemp, Warning, TEXT("HAHAHA"));
	//}

	DealDamageComponent = CreateDefaultSubobject<UDealDamageComponent>(TEXT("DamageComponent"));
	if (DealDamageComponent->GetTriggerCapsule()) {
		RootComponent = DealDamageComponent->GetTriggerCapsule();
	}
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	ParticleSystemComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AFireDamageActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFireDamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DealDamageComponent) {
		CurrentTimer += DeltaTime;

		if (CurrentTimer >= ToggleTime) {
			if (ParticleSystemComponent) {
				ParticleSystemComponent->ToggleActive();
			}
			DealDamageComponent->SetActive(!DealDamageComponent->IsActive());

			if (DealDamageComponent->IsActive()) {
				APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

				ATermOnePlayerCharacter* PlayerCharacter = Cast<ATermOnePlayerCharacter>(PlayerPawn);

				if (PlayerCharacter && DealDamageComponent->GetTriggerCapsule()->IsOverlappingActor(PlayerPawn)) {
					DealDamageComponent->DealDamage(PlayerCharacter);
				}
			}
			CurrentTimer = 0.0f;
		}
	}
}

