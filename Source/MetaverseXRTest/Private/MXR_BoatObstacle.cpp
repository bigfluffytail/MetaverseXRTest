// Fill out your copyright notice in the Description page of Project Settings.


#include "MXR_BoatObstacle.h"

#include "Components/SplineComponent.h"

// Sets default values
AMXR_BoatObstacle::AMXR_BoatObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Boat Mesh");
	MeshComp->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AMXR_BoatObstacle::BeginPlay()
{

	SplineComp = SplineRef->FindComponentByClass<USplineComponent>();
	Super::BeginPlay();
	
}

// Called every frame
void AMXR_BoatObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMXR_BoatObstacle::UpdateSplinePos(float alpha)
{

	float splineLength = SplineComp->GetSplineLength();
	float distance = FMath::Lerp(0, splineLength, alpha);

	if(distance > splineLength)
	{

		distance = distance - splineLength;
		
	}
	
	FVector newLoc = SplineComp->GetLocationAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World);
	FRotator newRot = SplineComp->GetRotationAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World);
	SetActorLocationAndRotation(newLoc, newRot);
	
	
}


