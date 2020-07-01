// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "Turret.generated.h"

class ATank;

UCLASS()
class TOONTANKS_API ATurret : public APawnBase{
	
	GENERATED_BODY()

public:

	ATurret();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRate = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRange = 500.f;

	void CheckFireCondition();
	
	float ReturnDistanceToPlayer();

	FTimerHandle FireRateTimerHandle;

	ATank* PlayerTank;

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
