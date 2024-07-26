// Fill out your copyright notice in the Description page of Project Settings.


#include "EUW_Parent.h"

#include "IDesktopPlatform.h"
#include "Misc/FileHelper.h"
#include "DesktopPlatformModule.h"

#include "Engine/Texture2D.h"
#include "Runtime/RenderCore/Public/RenderUtils.h"
#include "Runtime/ImageWrapper/Public/IImageWrapper.h"
#include "Runtime/ImageWrapper/Public/IImageWrapperModule.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMeshActor.h"

#include "Materials/MaterialInstanceDynamic.h"

#include "EditorUtilityLibrary.h"
#include "Engine/StaticMesh.h"
#include "Engine/Selection.h"
#include "GameFramework/Actor.h"

#include "Misc/Paths.h"
#include "HAL/PlatformProcess.h"
#include "HAL/FileManager.h"
#include "Misc/FeedbackContext.h"
#include "Editor/UnrealEd/Public/Editor.h"

void UEUW_Parent::EUWInitialization()
{
    SkyboxImagesLength = 0;
    CurrentImageIndex = -1;
    SkyboxMaterialInstance = nullptr;
    SelectedStaticMeshComponent = nullptr;
}

UTexture2D* UEUW_Parent::LoadTextureFromFile(const FString& FilePath)
{
    // Load image data from file
    TArray<uint8> FileData;
    if (!FFileHelper::LoadFileToArray(FileData, *FilePath))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load image file: %s"), *FilePath);
        return nullptr;
    }

    // Create image wrapper
    IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
    EImageFormat ImageFormat = ImageWrapperModule.DetectImageFormat(FileData.GetData(), FileData.Num());
    TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(ImageFormat);

    if (!ImageWrapper.IsValid() || !ImageWrapper->SetCompressed(FileData.GetData(), FileData.Num()))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to initialize image wrapper for: %s"), *FilePath);
        return nullptr;
    }

    // Create a TArray to hold the raw image data
    TArray<uint8> RawData;

    // Extract raw image data
    if (!ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, RawData))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get raw image data for: %s"), *FilePath);
        return nullptr;
    }

    // Create texture
    int32 Width = ImageWrapper->GetWidth();
    int32 Height = ImageWrapper->GetHeight();
    UTexture2D* Texture = UTexture2D::CreateTransient(Width, Height, PF_B8G8R8A8);

    if (!Texture)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create texture for: %s"), *FilePath);
        return nullptr;
    }

    // Copy data to texture
    void* TextureData = Texture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
    FMemory::Memcpy(TextureData, RawData.GetData(), RawData.Num());
    Texture->GetPlatformData()->Mips[0].BulkData.Unlock();

    // Update the texture resource
    Texture->UpdateResource();

    return Texture;
}

TArray<UTexture2D *> UEUW_Parent::LoadTexturesFromDirectory()
{
    // Get the Desktop Platform
    IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
    if (DesktopPlatform)
    {
        // Open Directory Picker Dialog
        FString FolderPath;
        const void* ParentWindowHandle = nullptr; // Optionally set to your window handle
        bool bOpened = DesktopPlatform->OpenDirectoryDialog(ParentWindowHandle, TEXT("Choose Image Directory"), TEXT(""), FolderPath);

        if (bOpened)
        {
            // Load image files from the selected directory
            TArray<FString> ImageFileNames;
            IFileManager::Get().FindFilesRecursive(ImageFileNames, *FolderPath, TEXT("*.png"), true, false, false);
            IFileManager::Get().FindFilesRecursive(ImageFileNames, *FolderPath, TEXT("*.jpg"), true, false, false);
            IFileManager::Get().FindFilesRecursive(ImageFileNames, *FolderPath, TEXT("*.jpeg"), true, false, false);

            for (const FString& FileName : ImageFileNames)
            {
                UTexture2D* Texture = LoadTextureFromFile(FileName);
                if (Texture)
                {
                    SkyboxImages.Add(Texture);
                }
            }
            SkyboxImagesLength = SkyboxImages.Num();
            UE_LOG(LogTemp, Log,
            TEXT("UEUW_Parent::LoadTexturesFromDirectory: SkyboxImagesLength: `%d`."),
            SkyboxImagesLength);
        }
    }

    return SkyboxImages;
}

void UEUW_Parent::LoadImagesToArray()
{
    this->LoadTexturesFromDirectory();
}


UTexture2D* UEUW_Parent::ShowNextImage()
{
    if (SkyboxImagesLength == 0 && CurrentImageIndex < 0)
    {
        UE_LOG(LogTemp, Log,
        TEXT("UEUW_Parent::ShowNextImage: The SkyboxImagesLength is equal zero and the CurrentImageIndex is negative - returning; `%d`-`%d`."),
        SkyboxImagesLength, CurrentImageIndex);

        return nullptr;
    }

    if (SkyboxImagesLength > 0 && CurrentImageIndex < SkyboxImagesLength - 1)
    {
        CurrentImageIndex++;
        UTexture2D* TextureToShow = SkyboxImages[CurrentImageIndex];
        SkyboxMaterialInstanceDynamic->SetTextureParameterValue("MainTexture", TextureToShow);
        
        UE_LOG(LogTemp, Log,
        TEXT("UEUW_Parent::ShowNextImage: - if - CurrentImageIndex: `%d`."),
        CurrentImageIndex);
        
        return TextureToShow;
    }
    else
    {
        CurrentImageIndex = -1;

        CurrentImageIndex++;
        UTexture2D* TextureToShow = SkyboxImages[CurrentImageIndex];
        
        UE_LOG(LogTemp, Log,
        TEXT("UEUW_Parent::ShowNextImage: - else - CurrentImageIndex: `%d`."),
        CurrentImageIndex);
        
        return TextureToShow;
    }
}

UTexture2D* UEUW_Parent::ShowPreviousImage()
{
    if (SkyboxImagesLength == 0 && CurrentImageIndex < 0)
    {
        UE_LOG(LogTemp, Log,
        TEXT("UEUW_Parent::ShowPreviousImage: The SkyboxImagesLength is equal zero and the CurrentImageIndex is negative - returning; `%d`-`%d`."),
        SkyboxImagesLength, CurrentImageIndex);

        return nullptr;
    }


    if (SkyboxImagesLength > 0 && CurrentImageIndex > 0)
    {
        CurrentImageIndex--;
        UTexture2D* TextureToShow = SkyboxImages[CurrentImageIndex];
        
        UE_LOG(LogTemp, Log,
        TEXT("UEUW_Parent::ShowPreviousImage: - if - CurrentImageIndex: `%d`."),
        CurrentImageIndex);
        
        return TextureToShow;
    }
    else
    {
        CurrentImageIndex = SkyboxImagesLength - 1;
        UTexture2D* TextureToShow = SkyboxImages[CurrentImageIndex];
        
        UE_LOG(LogTemp, Log,
        TEXT("UEUW_Parent::ShowPreviousImage: - else - CurrentImageIndex: `%d`."),
        CurrentImageIndex);
        
        return TextureToShow;
    }
}


void UEUW_Parent::PickStaticMeshFromLevel(FString &ActorName)
{
    // Clear previous selection
    SelectedStaticMeshComponent = nullptr;

    // Get the selected actors in the editor
    TArray<AActor*> SelectedActors;
    GEditor->GetSelectedActors()->GetSelectedObjects<AActor>(SelectedActors);

    for (AActor* Actor : SelectedActors)
    {
        if (Actor)
        {
            // Get all components of type UStaticMeshComponent
            TArray<UStaticMeshComponent*> MeshComponents;
            Actor->GetComponents<UStaticMeshComponent>(MeshComponents);

            for (UStaticMeshComponent* MeshComponent : MeshComponents)
            {
                UStaticMesh* StaticMesh = MeshComponent->GetStaticMesh();
                ActorName = StaticMesh->GetName();
                SelectedStaticMeshComponent = MeshComponent;
                this->AccessMaterialInstances();
            }
        }
    }
}

void UEUW_Parent::AccessMaterialInstances()
{
    if (SelectedStaticMeshComponent)
    {
        // Define the path to the material instance
        FString MaterialPath = TEXT("/Game/Level/Sky/MI_SkyDome.MI_SkyDome");
        UMaterial* MasterMaterial = LoadObject<UMaterial>(nullptr, *MaterialPath);
        SkyboxMaterialInstance = LoadObject<UMaterialInstance>(nullptr, *MaterialPath);
        SkyboxMaterialInstanceDynamic = UMaterialInstanceDynamic::Create(SkyboxMaterialInstance, SelectedStaticMeshComponent);

        if (SkyboxMaterialInstanceDynamic)
        {
            UE_LOG(LogTemp, Log, TEXT("UEUW_Parent::AccessMaterialInstances: SkyboxMaterialInstanceDynamic is not null."));
            SelectedStaticMeshComponent->SetMaterial(0, SkyboxMaterialInstanceDynamic);
        }

        UE_LOG(LogTemp, Log, TEXT("UEUW_Parent::AccessMaterialInstances: SelectedStaticMeshComponent is not null."));
    }
}
// void UEUW_Parent::LoadImagesToArray_Constructor()
// {
//     FString SelectedFolder;

//     IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
//     if (DesktopPlatform)
//     {
//         void* ParentWindowHandle = FSlateApplication::Get().GetActiveTopLevelWindow()->GetNativeWindow()->GetOSWindowHandle();
        
//         // Set the default path if needed
//         FString DefaultPath = FPaths::ProjectDir();
        
//         // Open the folder dialog
//         bool bFolderSelected = DesktopPlatform->OpenDirectoryDialog(
//             ParentWindowHandle,
//             TEXT("Select a folder"),
//             DefaultPath,
//             SelectedFolder
//         );

//         if (bFolderSelected)
//         {
//             // Log the selected folder path
//             UE_LOG(LogTemp, Warning, TEXT("Selected folder: %s"), *SelectedFolder);

//             // Define the image file extensions we want to load
//             const TArray<FString> ImageExtensions = { TEXT("png"), TEXT("jpg"), TEXT("jpeg"), TEXT("bmp"), TEXT("tga") };

//             // Get all files in the selected directory
//             TArray<FString> FoundFiles;
//             IFileManager& FileManager = IFileManager::Get();

//             // Use wildcard "*" to search for all files
//             FileManager.FindFiles(FoundFiles, *(SelectedFolder / TEXT("*")), true, false);

//             // Log the number of files found
//             UE_LOG(LogTemp, Warning, TEXT("Number of files found: %d"), FoundFiles.Num());

//             for (const FString& FileName : FoundFiles)
//             {
//                 UE_LOG(LogTemp, Warning, TEXT("Found file: %s"), *FileName);

//                 // Get the file extension
//                 FString FileExtension = FPaths::GetExtension(FileName).ToLower();

//                 // Check if the file is an image
//                 if (ImageExtensions.Contains(FileExtension))
//                 {
//                     // Construct the full file path
//                     FString FullFilePath = FPaths::Combine(SelectedFolder, FileName);
//                     SkyboxImagesPath += FullFilePath + TEXT("\n");
                    
//                     UE_LOG(LogTemp, Warning, TEXT("Full file path: %s"), *FullFilePath);
//                 }
//                 else
//                 {
//                     UE_LOG(LogTemp, Warning, TEXT("Skipped non-image file: %s"), *FileName);
//                 }
//             }
//             FString OutputFilePath = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("Editor_EUW_Skybox/SkyboxImages.tsv"));
//             FFileHelper::SaveStringToFile(SkyboxImagesPath, *OutputFilePath);
//         }
//         else
//         {
//             UE_LOG(LogTemp, Warning, TEXT("No folder selected."));
//         }
//     }
//     else
//     {
//         UE_LOG(LogTemp, Error, TEXT("DesktopPlatform not available."));
//     }
// }