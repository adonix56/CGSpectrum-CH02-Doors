// Fill out your copyright notice in the Description page of Project Settings.


#include "DealDamageComponent.h"
#include "TermOnePlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/DamageType.h"
#include "Engine/DamageEvents.h"

// Sets default values for this component's properties
UDealDamageComponent::UDealDamageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("TriggerCapsuleComponent"));
	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &UDealDamageComponent::OnOverlapBegin);
	TriggerCapsule->OnComponentEndOverlap.AddDynamic(this, &UDealDamageComponent::OnOverlapEnd);
	// ...
}

void UDealDamageComponent::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	UE_LOG(LogTemp, Warning, TEXT("UDealDamageComponent::OnOverlapBegin"));
	if (!bActive || OtherActor == GetOwner()) {
		return;
	}

	ATermOnePlayerCharacter* PlayerCharacter = Cast<ATermOnePlayerCharacter>(OtherActor);
	if (PlayerCharacter) {
		DealDamage(PlayerCharacter);
	}
}

void UDealDamageComponent::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	UE_LOG(LogTemp, Warning, TEXT("UDealDamageComponent::OnOverlapEnd"));
}

void UDealDamageComponent::DealDamage(ATermOnePlayerCharacter* PlayerCharacter) {
	TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
	FDamageEvent DamageEvent(ValidDamageTypeClass);

	PlayerCharacter->TakeDamage(BaseDamage, DamageEvent, nullptr, GetOwner());
}

// Called when the game starts
void UDealDamageComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

