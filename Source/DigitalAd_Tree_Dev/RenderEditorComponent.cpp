// Fill out your copyright notice in the Description page of Project Settings.


#include "RenderEditorComponent.h"
#include "Engine/Engine.h"

#include "EmissionController.h"
#include "Kismet/GameplayStatics.h"
#include "ParentActor.h"

URenderEditorComponent::URenderEditorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void URenderEditorComponent::BeginPlay()
{
	Super::BeginPlay();

    AActor* Owner = GetOwner();
    if(Owner)
    {
        CameraActor = Owner;
        EndPosition = FVector(1080.0f, 0.0f, 200.0f);
        Distance = FVector::Dist(EndPosition, CameraActor->GetActorLocation());
        this->CalculateDistance_Timer();
    }
}

void URenderEditorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// this->CameraCurrentTransform();
}

void URenderEditorComponent::CameraCurrentTransform()
{
    if (CameraActor)
    {
        CameraTransform = CameraActor->GetActorTransform();
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("CameraActor is not set"));
    }
}

void URenderEditorComponent::StartIncrementing()
{
	GetWorld()->GetTimerManager().SetTimer(IncrementTimerHandle, this, &URenderEditorComponent::IncrementFloatValue, 1.0f, true);
}

void URenderEditorComponent::IncrementFloatValue()
{
    if (Var < 10.0f)
    {
        Var += 1.0f;
		UE_LOG(LogTemp, Warning, TEXT("URenderEditorComponent::IncrementFloatValue: The Var is less then 10."));
    }
    else
    {
		Var = 0.0f;
        GetWorld()->GetTimerManager().ClearTimer(IncrementTimerHandle);
    }
}

void URenderEditorComponent::CalculateDistance_Timer()
{
    GetWorld()->GetTimerManager().SetTimer(IncrementTimerHandle, this, &URenderEditorComponent::CalculateDistance, 0.01f, true);
}

void URenderEditorComponent::CalculateDistance()
{
    if(CameraActor && Distance > 1000)
    {
        Distance = FVector::Dist(EndPosition, CameraActor->GetActorLocation());
    }
    else
    {
        this->PlayMedia();
        this->IncreaseEmission();
        GetWorld()->GetTimerManager().ClearTimer(IncrementTimerHandle);
    }
}

void URenderEditorComponent::PlayMedia()
{
    UClass* BlueprintClass = LoadObject<UClass>(nullptr, TEXT("/Game/Level/BlockoutElements/ParentActor.ParentActor_C"));
    if (BlueprintClass)
    {
        TArray<AActor*> FoundActors;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), BlueprintClass, FoundActors);
        for(AActor* FoundActor : FoundActors)
        {
            AParentActor* ParentActorInstance = Cast<AParentActor>(FoundActor);
            if (ParentActorInstance)
            {
                ParentActorInstance->SetUpMediaPlayers();
                UE_LOG(LogTemp, Log, TEXT("The ParentActorInstance is found."));
            }
        }

        UE_LOG(LogTemp, Log, TEXT("The ParentActor is found."));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("The ParentActor is nullptr."));
    }
}

void URenderEditorComponent::IncreaseEmission()
{
    // Find all actors in the world
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FoundActors);

    for (AActor* FoundActor : FoundActors)
    {
        // Find the specific component instance attached to the actor
        UEmissionController* EmissionControllerComponent = FoundActor->FindComponentByClass<UEmissionController>();
        if (EmissionControllerComponent)
        {
            // Log the name of the component to verify it's found
            UE_LOG(LogTemp, Log, TEXT("Found EmissionController component on actor: %s"), *FoundActor->GetName());

            // Directly call the Timer function on the component instance
            EmissionControllerComponent->IncreaseStaticEmissionParam_Timer();
        }
    }
}