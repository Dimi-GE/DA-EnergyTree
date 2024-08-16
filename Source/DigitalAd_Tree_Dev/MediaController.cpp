// Fill out your copyright notice in the Description page of Project Settings.


#include "MediaController.h"

// Multimedia
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "MediaSoundComponent.h"
#include "FileMediaSource.h"

// Sets default values for this component's properties
UMediaController::UMediaController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMediaController::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMediaController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMediaController::PlayPreparedMedia()
{
	if(MediaPlayer1 && MediaSource1)
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

	if (MediaPlayer2 && MediaSource2)
	{
		MediaPlayer2->OpenSource(MediaSource2);
		MediaPlayer2->Play();
		UE_LOG(LogTemp, Log, TEXT("AContentViewer::BeginPlay: MediaPlayer2 is set."));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("AContentViewer::BeginPlay: MediaPlayer2 is nullptr - returnung."));
		return;
	}
}