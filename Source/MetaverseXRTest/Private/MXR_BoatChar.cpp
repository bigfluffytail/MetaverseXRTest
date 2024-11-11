// Fill out your copyright notice in the Description page of Project Settings.


#include "MXR_BoatChar.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AMXR_BoatChar::AMXR_BoatChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	MeshComp->SetupAttachment(RootComponent);

	//Spring arm creation for camera manipulation
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArmComponent->SetupAttachment(MeshComp);
	
	//Camera component creation + attachment
	CameraComp = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	CameraComp->SetupAttachment(SpringArmComponent);
	
}

// Called when the game starts or when spawned
void AMXR_BoatChar::BeginPlay()
{
	Super::BeginPlay();

	//If the player controller is active..
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		//Check if we're using the enhanced input subsystem
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			//If we are, add our defined IMC to the system so our inputs can be read!
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
}

// Called every frame
void AMXR_BoatChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// If our steer input value is above or below 0, then we lerp to whatever the maxed out input is
	// this is either -1 or 1 depending on direction pressed
	if(steerValue != 0)
	{

		steerSpeed = FMath::Lerp(steerSpeed, steerValue, 0.25 * DeltaTime);
		
	}

	// Otherwise, lerp back to 0
	else if(steerValue == 0)
	{

		steerSpeed = FMath::Lerp(steerSpeed, 0, 2 * DeltaTime);
		
	}


	// Get the current mesh rotation, then modify the rotation depending on inputs
	// This will rotate the pitch to -10 to 10 depending on forward / back throttle
	// and will rotate -15 to 15 depending on the left / right turn value
	FRotator currentRot = MeshComp->GetRelativeRotation();
	currentRot.Pitch = FMath::Lerp(currentRot.Pitch, 10 * throttleValue, 1 * DeltaTime);
	currentRot.Roll = FMath::Lerp(currentRot.Roll, 15 * steerValue, 0.5 * DeltaTime);
	MeshComp->SetRelativeRotation(FRotator(currentRot.Pitch, currentRot.Yaw, currentRot.Roll));

	// We're also adding some slower rotation depending on our prior inputs.
	// The reason this is outside of the if statements is so our lerp back to 0
	// works as intended.
	MeshComp->AddLocalRotation(FRotator(0, steerSpeed, 0));
	
	
}

void AMXR_BoatChar::Throttle(const FInputActionValue& Value)
{

	// Check what our W / S input value is
	throttleValue = Value.Get<float>();

	//Ideally we wouldn't have to get Capsule Component and we would just be getting the reference above,
	//but it's pretty harmless here. I could set a reference to it, or ideally just have access to it
	//but this is fine as is.
	GetCapsuleComponent()->AddForce(MeshComp->GetForwardVector() * (throttleSpeed * throttleValue), NAME_None, true);
	
}


void AMXR_BoatChar::Steer(const FInputActionValue& Value)
{

	// Check what our A / D input value is
	steerValue = Value.Get<float>();
	
}

// Called to bind functionality to input
void AMXR_BoatChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// If we can get the EnhancedInputComponent, prep our inputs
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Move Action
		// Every time W or S is pressed, run the Throttle function
		EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Triggered, this, &AMXR_BoatChar::Throttle);

		// Turning inputs
		// Every time A or D is pressed, or let go, run the Steer function
		EnhancedInputComponent->BindAction(SteerAction, ETriggerEvent::Triggered, this, &AMXR_BoatChar::Steer);
		EnhancedInputComponent->BindAction(SteerAction, ETriggerEvent::Canceled, this, &AMXR_BoatChar::Steer);
		EnhancedInputComponent->BindAction(SteerAction, ETriggerEvent::Completed, this, &AMXR_BoatChar::Steer);

	}
	
}

