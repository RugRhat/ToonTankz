// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


ATank::ATank(){

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void ATank::BeginPlay(){
	
    Super::BeginPlay();
	
}


// Called every frame
void ATank::Tick(float DeltaTime){

	Super::Tick(DeltaTime);

    Rotate();
    Move();
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){

	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &ATank::CalculateMoveInput);
    PlayerInputComponent->BindAxis("Turn", this, &ATank::CalculateRotateInput);
}


void ATank::CalculateMoveInput(float Value){

    MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
}


void ATank::CalculateRotateInput(float Value){

    float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;

    FRotator Rotation = FRotator(0, RotateAmount, 0);

    RotationDirection = FQuat(Rotation);
}


void ATank::Move(){

    AddActorLocalOffset(MoveDirection, true);
}


void ATank::Rotate(){

    AddActorLocalRotation(RotationDirection, true);
}