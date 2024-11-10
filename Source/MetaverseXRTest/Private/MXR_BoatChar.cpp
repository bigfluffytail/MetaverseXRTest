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
	SpringArmComponent->SetupAttachment(RootComponent);
	
	//Camera component creation + attachment
	CameraComp = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	CameraComp->SetupAttachment(SpringArmComponent);
	
}

// Called when the game starts or when spawned
void AMXR_BoatChar::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
}

// Called every frame
void AMXR_BoatChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMXR_BoatChar::Throttle(const FInputActionValue& Value)
{

	float throttleValue = Value.Get<float>();

	if(Controller != nullptr)
	{

		AddMovementInput(GetActorForwardVector(), throttleValue);
		
	}
	
}


void AMXR_BoatChar::Steer(const FInputActionValue& Value)
{

	float steerValue = Value.Get<float>();
	if(Controller != nullptr)
	{

		AddControllerYawInput(steerValue);
		
	}
	
}

// Called to bind functionality to input
void AMXR_BoatChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Moving
		EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Triggered, this, &AMXR_BoatChar::Throttle);

		//Turning
		EnhancedInputComponent->BindAction(SteerAction, ETriggerEvent::Triggered, this, &AMXR_BoatChar::Steer);

	}
	
}

