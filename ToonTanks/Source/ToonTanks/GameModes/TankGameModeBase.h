// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

class ATank;
class ATurret;
class APlayerControllerBase;

UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon);

	void ActorDied(AActor* DeadActor);
	

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player", meta = (AllowPrivateAccess = "true"))
	ATank* PlayerTank;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Loop", meta = (AllowPrivateAccess = "true"))
	int StartDelay = 4;

	void HandleGameStart();
	void HandleGameOver(bool PlayerWon);

	int32 GetTargetTurretCount();

	APlayerControllerBase* PlayerControllerRef;

	int32 TargetTurrets = 0;

protected:

	virtual void BeginPlay() override;
};
