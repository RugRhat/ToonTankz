// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"


ATurret::ATurret(){

}


// Called when the game starts or when spawned
void ATurret::BeginPlay(){
	
    Super::BeginPlay();

    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &ATurret::CheckFireCondition, FireRate, true, false);

    PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}


// Called every frame
void ATurret::Tick(float DeltaTime){

	Super::Tick(DeltaTime);

    if(!PlayerTank || ReturnDistanceToPlayer() > FireRange){return;}

    RotateTurret(PlayerTank->GetActorLocation());
}


void ATurret::CheckFireCondition(){

    // If player == null || is dead: BAIL!
    if(!PlayerTank){return;}

    // If player is in range then: FIRE!
    if(ReturnDistanceToPlayer() <= FireRange){
        Fire();
    }
}


float ATurret::ReturnDistanceToPlayer(){

    if(!PlayerTank){return 0.f;}

   return (PlayerTank->GetActorLocation() - GetActorLocation()).Size();
}


void ATurret::HandleDestruction(){

    Super::HandleDestruction();

    Destroy();
}