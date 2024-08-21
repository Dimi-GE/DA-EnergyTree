// Fill out your copyright notice in the Description page of Project Settings.

// Related Actors/Components
#include "ContentViewer.h"
#include "UMG_ContentViewer.h"
#include "CineCameraActor.h"
// Utilities
#include "Misc/Paths.h"
#include "Engine/Texture2D.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
// Multimedia
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "MediaSoundComponent.h"
#include "FileMediaSource.h"
// UI
#include "Components/WidgetComponent.h"
#include "Components/Image.h"
// Materials
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
AContentViewer::AContentViewer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ViewerComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("ViewerContentReflector"), true);
	// ViewerComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AContentViewer::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AContentViewer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AContentViewer::SetParentForSelf()
{
    ParentActor = Cast<ACineCameraActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ACineCameraActor::StaticClass()));
    if (ParentActor)
    {
		// UE_LOG(LogTemp, Log, TEXT("AContentViewer::SetParentToSelf: `%s`."), *ParentActor->GetName());
		this->AttachToActor(ParentActor, FAttachmentTransformRules::KeepRelativeTransform);
    }
	else
	{
		UE_LOG(LogTemp, Log, TEXT("AContentViewer::SetParentToSelf: No CineCameraActor found - returning."));
		return;
	}
}

void AContentViewer::SetUpMediaPlayer()
{
	if(MediaPlayer1)
	{
		MediaPlayer1->OpenSource(MediaSource1);
		MediaPlayer1->Play();
		UE_LOG(LogTemp, Log, TEXT("AContentViewer::BeginPlay: MediaPlayer1 is set."));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("AContentViewer::BeginPlay: MediaPlayer1 is nullptr - returnung."));
		return;
	}
}

void AContentViewer::ResetReferences()
{
	ParentActor = nullptr;
}

void AContentViewer::DetachSelfFromParent()
{
    if (GetAttachParentActor() != nullptr)
    {
        DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
    }
}
