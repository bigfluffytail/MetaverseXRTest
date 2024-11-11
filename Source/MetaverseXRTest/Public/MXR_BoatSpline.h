// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MXR_BoatSpline.generated.h"

class USplineComponent;

UCLASS()
class METAVERSEXRTEST_API AMXR_BoatSpline : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMXR_BoatSpline();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USplineComponent* SplineComp;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
