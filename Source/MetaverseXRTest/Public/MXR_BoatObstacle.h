// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MXR_BoatSpline.h"
#include "GameFramework/Actor.h"
#include "MXR_BoatObstacle.generated.h"

class UStaticMeshComponent;

UCLASS()
class METAVERSEXRTEST_API AMXR_BoatObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMXR_BoatObstacle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void UpdateSplinePos(float alpha);
	
	UPROPERTY(EditAnywhere)
	AMXR_BoatSpline* SplineRef;

	USplineComponent* SplineComp;

};
