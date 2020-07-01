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
}


void ATurret::CheckFireCondition(){

    // If player == null || is dead: BAIL!
    if(!PlayerTank){
        return;
    }

    // If player is in range then: FIRE!
    if(ReturnDistanceToPlayer() <= FireRange){
        // Fire
        UE_LOG(LogTemp, Warning, TEXT("FIRE!!"));
    }
}


float ATurret::ReturnDistanceToPlayer(){

    if(!PlayerTank){
        return 0.f;
    }

   return (PlayerTank->GetActorLocation() - GetActorLocation()).Size();
}