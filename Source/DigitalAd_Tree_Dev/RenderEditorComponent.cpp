// Fill out your copyright notice in the Description page of Project Settings.


#include "RenderEditorComponent.h"
#include "Engine/Engine.h"

#include "ContentViewer.h"
#include "EmissionController.h"
#include "MediaController.h"
#include "Kismet/GameplayStatics.h"
// #include "ParentActor.h"

URenderEditorComponent::URenderEditorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void URenderEditorComponent::BeginPlay()
{
	Super::BeginPlay();

    this->OwnerInit();
    this->ContentViewerActorInit();
    if (Owner)
    {
        // this->TrackCurrentPosition_Timer();
        this->StartCountdown();
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("URenderEditorComponent::BeginPlay: The Owner is nullptr."));
        return;
    }
}

void URenderEditorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void URenderEditorComponent::OwnerInit()
{
    Owner = GetOwner();
    if (Owner)
    {
        CameraActor = Owner;
        CameraPathLength = CameraPath.Num() - 1;
        Distance = 11;
        CurrentPositionIndex = 0;
        CurrentRenderOrder = 0;
        TimerRenderCounter = 0;
        GetWorld()->GetTimerManager().ClearTimer(CurrentPositionTimerHandle);
        GetWorld()->GetTimerManager().ClearTimer(ManualTimerHandle);
    }
}

void URenderEditorComponent::ContentViewerActorInit()
{
    AContentViewer* ContentViewerActorRef = Cast<AContentViewer>(UGameplayStatics::GetActorOfClass(GetWorld(), AContentViewer::StaticClass()));

    if (ContentViewerActorRef)
    {
        ContentViewerActor = ContentViewerActorRef;
        ContentViewerActor->SetParentForSelf();
        ContentViewerActor->SetActorRelativeLocation(FVector(150.f, 0.f, 0.f));
        ContentViewerActor->SetActorRelativeRotation(FRotator(0.f, 180.f, 0.f));
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("URenderEditorComponent::ContentViewerActorInit: The ContentViewerActor was not found - returning."));
        return;
    }
}

void URenderEditorComponent::RE_InvokeEmissionController()
{
    CurrentRenderOrder += 1;
    // Find all actors in the world
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FoundActors);

    for (AActor* FoundActor : FoundActors)
    {
        // Find the specific component instance attached to the actor
        UEmissionController* EmissionControllerComponent = FoundActor->FindComponentByClass<UEmissionController>();

        if (EmissionControllerComponent)
        {
            if (EmissionControllerComponent->RenderOrder == CurrentRenderOrder)
            {
                EmissionControllerComponent->IncreaseEmissionParamDynamic();
                UE_LOG(LogTemp, Log, TEXT("Found EmissionController component on actor `%s` with index `%d`"), *FoundActor->GetName(), EmissionControllerComponent->RenderOrder);
            }
        }
    }
}

void URenderEditorComponent::InvokeMediaControllerAtTime()
{

    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FoundActors);

    for (AActor* FoundActor : FoundActors)
    {
        // Find the specific component instance attached to the actor
        UMediaController* MediaControllerComponent = FoundActor->FindComponentByClass<UMediaController>();

        if (MediaControllerComponent)
        {
            if (MediaControllerComponent->RenderAtSecond == TimerRenderCounter)
            {
                MediaControllerComponent->PlayPreparedMedia();
                UE_LOG(LogTemp, Log, TEXT("Found MediaController component on actor `%s` with RenderAtSecond `%d`"), *FoundActor->GetName(), MediaControllerComponent->RenderAtSecond);
            }
        }
    }
    // UClass* BlueprintClass = LoadObject<UClass>(nullptr, TEXT("/Game/Level/BlockoutElements/ParentActor.ParentActor_C"));
    // if (BlueprintClass)
    // {
    //     TArray<AActor*> FoundActors;
    //     UGameplayStatics::GetAllActorsOfClass(GetWorld(), BlueprintClass, FoundActors);
    //     for(AActor* FoundActor : FoundActors)
    //     {
    //         AParentActor* ParentActorInstance = Cast<AParentActor>(FoundActor);
    //         if (ParentActorInstance)
    //         {
    //             ParentActorInstance->SetUpMediaPlayers();
    //             UE_LOG(LogTemp, Log, TEXT("The ParentActorInstance is found."));
    //         }
    //     }

    //     UE_LOG(LogTemp, Log, TEXT("The ParentActor is found."));
    // }
    // else
    // {
    //     UE_LOG(LogTemp, Warning, TEXT("The ParentActor is nullptr."));
    // }
}

void URenderEditorComponent::StartCountdown()
{
    GetWorld()->GetTimerManager().SetTimer(ManualTimerHandle,
    [this]()
    {
        if (TimerRenderCounter < 15)
        {
            TimerRenderCounter += 1;
            this->InvokeEmissionControllerAtTime();
            this->InvokeMediaControllerAtTime();
            UE_LOG(LogTemp, Log, TEXT("URenderEditorComponent::StartCountdown: `%i`."), TimerRenderCounter);
        }
        else
        {
            TimerRenderCounter = 0;
            GetWorld()->GetTimerManager().ClearTimer(ManualTimerHandle);
            return;
        }

    },
    1.0f, true);
}

void URenderEditorComponent::InvokeEmissionControllerAtTime()
{
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FoundActors);

    for (AActor* FoundActor : FoundActors)
    {
        // Find the specific component instance attached to the actor
        UEmissionController* EmissionControllerComponent = FoundActor->FindComponentByClass<UEmissionController>();

        if (EmissionControllerComponent)
        {
            if (EmissionControllerComponent->RenderAtSecond == TimerRenderCounter)
            {
                EmissionControllerComponent->IncreaseEmissionParamDynamic();
                UE_LOG(LogTemp, Log, TEXT("Found EmissionController component on actor `%s` with RenderAtSecond `%d`"), *FoundActor->GetName(), EmissionControllerComponent->RenderAtSecond);
            }
        }
    }
}

void URenderEditorComponent::TrackCurrentPosition_Timer()
{
    if(Owner == nullptr || CameraActor == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("The WorldContext or CameraActor is nullptr - returning."));
        GetWorld()->GetTimerManager().ClearTimer(CurrentPositionTimerHandle);
        return;
    }

    GetWorld()->GetTimerManager().SetTimer(CurrentPositionTimerHandle,
    [this]()
    {
        if(Owner && Distance > 10)
        {
            CurrentPosition = CameraActor->GetActorLocation();
            Distance = FVector::Dist(CurrentPosition, CameraPath[CurrentPositionIndex]);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("URenderEditorComponent::TrackCurrentPosition_Timer: RE_ function launched."));
            this->RE_CalculateDistance();
            this->RE_InvokeEmissionController();
        }  
    },
    0.01f, true);
}

void URenderEditorComponent::RE_CalculateDistance()
{
    if (CurrentPositionIndex < CameraPathLength)
    {
        CurrentPositionIndex += 1;
        Distance = FVector::Dist(CurrentPosition, CameraPath[CurrentPositionIndex]);
        this->TrackCurrentPosition_Timer();
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("URenderEditorComponent::CalculateDistance: The CurrentPositionIndex overflows CameraPathLength - returning."));
        GetWorld()->GetTimerManager().ClearTimer(CurrentPositionTimerHandle);
        return;
    }
}