// Fill out your copyright notice in the Description page of Project Settings.

#include "AI_Mutant_Controller.h"
#include "AIMutant.h"
#include "MutantWayPoint.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "TheForgottenOnesCharacter.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AAI_Mutant_Controller::AAI_Mutant_Controller() {

	PrimaryActorTick.bCanEverTick = true;
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

	SightConfig->SightRadius = AISightRadius;
	SightConfig->LoseSightRadius = AILoseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = AIFieldofView;
	SightConfig->SetMaxAge(AISightAge);

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AAI_Mutant_Controller::OnPawnDetected);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
}

void AAI_Mutant_Controller::BeginPlay()
{
	Super::BeginPlay();

	if (GetPerceptionComponent() != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("All Systems Set"));
	}

	else {
		UE_LOG(LogTemp, Warning, TEXT("Faliure Warning"));
	}

}

void AAI_Mutant_Controller::Possess(APawn * Pawn)
{
	Super::Possess(Pawn);

}

void AAI_Mutant_Controller::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AAIMutant* Character = Cast<AAIMutant>(GetPawn());

	if (DistanceToPlayer > AISightRadius) {

		bIsPLayerDetected = false;
	}

	/*if (DistanceToPlayer == AILoseSightRadius) {


	}

	*/
	if (Character->NextWaypoint != nullptr && bIsPLayerDetected == false) {
		MoveToActor(Character->NextWaypoint, 5.0f);
	}

	else if (bIsPLayerDetected == true) {

		ATheForgottenOnesCharacter* Player = Cast<ATheForgottenOnesCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		MoveToActor(Player, 5.0);
	}
	
	

}

FRotator AAI_Mutant_Controller::GetControlRotation() const
{
	if (GetPawn() == nullptr)
	{
	return FRotator();
	}

	return FRotator(0.0f, GetPawn()->GetActorRotation().Yaw, 0.0f);
}

void AAI_Mutant_Controller::OnPawnDetected(TArray<AActor*> DetectedPawns)
{
	/*if (DetectedPawns.Num() > 0) {
		UE_LOG(LogTemp, Warning, TEXT("Player Has Entered F.O.V"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player Has Left F.O.V"));


	}
	*/

	for (size_t i = 0; i < DetectedPawns.Num(); i++) {

		DistanceToPlayer = GetPawn()->GetDistanceTo(DetectedPawns[i]);
		UE_LOG(LogTemp, Warning, TEXT("Distance: %f"), DistanceToPlayer);

	}

	bIsPLayerDetected = true;


}
