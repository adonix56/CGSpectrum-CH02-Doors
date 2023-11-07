// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"
//#include "GameFramework/PlayerController.h"
//#include "GameFramework/DamageType.h"
#include "TermOnePlayerCharacter.h"

// Sets default values
ATermOnePlayerCharacter::ATermOnePlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
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
	OnDeath(true);
}

void ATermOnePlayerCharacter::OnDeath(bool IsFellOut) {
	APlayerController* PlayerController = GetController<APlayerController>();
	if (PlayerController) {
		PlayerController->RestartLevel();
	}
}

float ATermOnePlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) {
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	UE_LOG(LogTemp, Warning, TEXT("ATermOnePlayerCharacteR::TakeDamage Damage %.2f"), Damage);
	if (HealthComponent) {
		HealthComponent->TakeDamage(Damage);
		//TODO: Try adding this logic to the HealthComponent. Get Owner, cast as ATermOnePlayerCharacter then call OnDeath(false)
		if (HealthComponent->IsDead()) {
			OnDeath(false);
		}
	}

	return Damage;
}