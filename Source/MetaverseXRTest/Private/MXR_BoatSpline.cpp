// Fill out your copyright notice in the Description page of Project Settings.


#include "MXR_BoatSpline.h"

#include "Components/SplineComponent.h"

// Sets default values
AMXR_BoatSpline::AMXR_BoatSpline()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SplineComp = CreateDefaultSubobject<USplineComponent>("Spline");
	SplineComp->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AMXR_BoatSpline::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMXR_BoatSpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

