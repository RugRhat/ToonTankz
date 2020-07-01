// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/Tank.h"
#include "ToonTanks/Pawns/Turret.h"
#include "Kismet/GameplayStatics.h"


void ATankGameModeBase::BeginPlay(){

    TargetTurrets = GetTargetTurretCount();
    PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    HandleGameStart();
    
    Super::BeginPlay();
}


int32 ATankGameModeBase::GetTargetTurretCount(){

    TSubclassOf<ATurret> ClassToFind;
    ClassToFind = ATurret::StaticClass(); 
    TArray<AActor*> TurretActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, TurretActors);

    return TurretActors.Num();
}


void ATankGameModeBase::HandleGameStart(){

    GameStart();
}


void ATankGameModeBase::HandleGameOver(bool PlayerWon){

    GameOver(PlayerWon);
}


void ATankGameModeBase::ActorDied(AActor* DeadActor){

    if(DeadActor == PlayerTank){
        PlayerTank->PawnDestroyed();
        HandleGameOver(false);
    } else if(ATurret* DestroyedTurret = Cast<ATurret>(DeadActor)){
        DestroyedTurret->PawnDestroyed();
        
        TargetTurrets --;

        if(TargetTurrets == 0){
            HandleGameOver(true);
        }
    }
}