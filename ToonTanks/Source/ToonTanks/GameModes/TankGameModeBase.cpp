// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/Tank.h"
#include "ToonTanks/Pawns/Turret.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"
#include "Kismet/GameplayStatics.h"


void ATankGameModeBase::BeginPlay(){

    TargetTurrets = GetTargetTurretCount();
    PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

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

    if(PlayerControllerRef){
            PlayerControllerRef->SetPlayerEnabledState(false);
    
            FTimerHandle PlayerEnableHandle;
            FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef, &APlayerControllerBase::SetPlayerEnabledState, true);
    
            GetWorldTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
    }
}


void ATankGameModeBase::HandleGameOver(bool PlayerWon){

    GameOver(PlayerWon);
}


void ATankGameModeBase::ActorDied(AActor* DeadActor){

    if(DeadActor == PlayerTank){
        PlayerTank->PawnDestroyed();
        HandleGameOver(false);

        if(PlayerControllerRef){
            PlayerControllerRef->SetPlayerEnabledState(false);
        }
    } else if(ATurret* DestroyedTurret = Cast<ATurret>(DeadActor)){
        DestroyedTurret->PawnDestroyed();
        
        TargetTurrets --;

        if(TargetTurrets == 0){
            HandleGameOver(true);
        }
    }
}