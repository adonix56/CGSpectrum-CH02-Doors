// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/DamageType.h"
#include "DamageHandlerComponent.h"
#include "TermOnePlayerCharacter.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ATermOnePlayerCharacter::ATermOnePlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	DamageHandlerComponent = CreateDefaultSubobject<UDamageHandlerComponent>(TEXT("DamageHandlerComponent"));
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
	ParticleSystemComponent->SetupAttachment(RootComponent);
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

	FInputActionBinding* Binding;
	Binding = &PlayerInputComponent->BindAction(FName("InteractionStart"), IE_Pressed, this, &ATermOnePlayerCharacter::StartInteraction);
	Binding = &PlayerInputComponent->BindAction(FName("InteractionStop"), IE_Pressed, this, &ATermOnePlayerCharacter::StopInteraction);
}

void ATermOnePlayerCharacter::FellOutOfWorld(const UDamageType& dmgType) {
	if (HealthComponent && !HealthComponent->IsDead()) {
		HealthComponent->SetHealth(0.0f);
		OnDeath(true);
	}
}

void ATermOnePlayerCharacter::OnDeath(bool IsFellOut) {
	APlayerController* PlayerController = GetController<APlayerController>();
	if (PlayerController) {
		PlayerController->DisableInput(PlayerController);
	}
	GetWorld()->GetTimerManager().SetTimer(RestartLevelTimerHandle, this, &ATermOnePlayerCharacter::OnDeathTimerFinished, TimeRestartLevelAfterDeath, false);
}

void ATermOnePlayerCharacter::OnDeathTimerFinished()
{
	APlayerController* PlayerController = GetController<APlayerController>();
	if (PlayerController) {
		PlayerController->RestartLevel();
	}
}

float ATermOnePlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) {
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	UE_LOG(LogTemp, Warning, TEXT("ATermOnePlayerCharacteR::TakeDamage Damage %.2f"), Damage);
	if (HealthComponent && !HealthComponent->IsDead()) {
		HealthComponent->TakeDamage(Damage);
		if (HealthComponent->IsDead()) {
			OnDeath(false);
		}
	}

	return Damage;
}

void ATermOnePlayerCharacter::SetOnFire(float BaseDamage, float DamageTotalTime, float TakeDamageInterval)
{
	if (DamageHandlerComponent) {
		DamageHandlerComponent->TakeFireDamage(BaseDamage, DamageTotalTime, TakeDamageInterval);
	}
}

const bool ATermOnePlayerCharacter::IsAlive() const
{
	if (HealthComponent) {
		return !HealthComponent->IsDead();
	}
	return false;
}

const float ATermOnePlayerCharacter::GetCurrentHealth() const
{
	if (HealthComponent) { 
		return HealthComponent->GetCurrentHealth(); 
	}
	return 0.0f;
}

void ATermOnePlayerCharacter::StartInteraction() {
	OnInteractionStart.Broadcast();
}

void ATermOnePlayerCharacter::StopInteraction() {
	OnInteractionCancel.Broadcast();
}