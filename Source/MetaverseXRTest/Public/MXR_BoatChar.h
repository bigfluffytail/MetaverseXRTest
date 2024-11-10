// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "MXR_BoatChar.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class METAVERSEXRTEST_API AMXR_BoatChar : public ACharacter
{
	GENERATED_BODY()

	//Input stuff here
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* ThrottleAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* SteerAction;

public:
	// Sets default values for this character's properties
	AMXR_BoatChar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	//Relevant components here
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;
	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	//Throttle Function
	void Throttle(const FInputActionValue& Value);
	//Steer Function
	void Steer(const FInputActionValue& Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
