// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AI_Mutant_Controller.generated.h"

/**
 * 
 */
UCLASS()
class THEFORGOTTENONES_API AAI_Mutant_Controller : public AAIController
{
	GENERATED_BODY()

public:
		AAI_Mutant_Controller();

		virtual void BeginPlay() override;

		virtual void Possess(APawn* Pawn) override;

		virtual void Tick(float DeltaSeconds) override;

		virtual FRotator GetControlRotation() const override;
	
		UFUNCTION()
			void OnPawnDetected(TArray<AActor*> DetectedPawns);

		UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = AI)
			float AISightRadius = 800.0f;

		UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = AI)
			float AISightAge = 5.0f;

		UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = AI)
			float AILoseSightRadius = AISightRadius + 200.0f;

		UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = AI)
			float AIFieldofView = 180.0f;

		UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = AI)
			class UAISenseConfig_Sight * SightConfig;

		UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = AI)
			bool bIsPLayerDetected = false;

		UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = AI)
			float DistanceToPlayer = 0.0f;



};
