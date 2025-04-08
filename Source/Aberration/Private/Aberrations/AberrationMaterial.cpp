// Copyright (c) 2024, Jasbrela. All rights reserved.


#include "Aberrations/AberrationMaterial.h"

#include "DebugMacros.h"

AAberrationMaterial::AAberrationMaterial() {

	/*Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);*/
}

void AAberrationMaterial::BeginPlay()
{
	Super::BeginPlay();

	if (Mesh == nullptr)
	{
		LOG_ERROR("Failed to set up AberrationMaterial: %s", *GetName());
		return;
	}
	
	TArray<UStaticMeshComponent*> Meshes;
	Mesh->GetComponents<UStaticMeshComponent>(Meshes);

	// TODO: Optimize
	for (int i = 0; i < Data.Num(); i++)
	{
		for (UStaticMeshComponent* MeshComponent : Meshes)
		{
			if (MeshComponent == nullptr) continue;
			
			if (MeshComponent)
			{
				FString Name = MeshComponent->GetName();
				FString ComponentName = Data[i].MeshComponentName.ToString();
				
				if (Name == ComponentName)
				{
					Data[i].MeshComponent = MeshComponent;
					//LOG_SUCCESS("Found Mesh with name: %s", *ComponentName);
					break;
				}// else LOG("Not found. [%s] -> [%s]", *Name, *ComponentName);

			}
		}
	}
}

void AAberrationMaterial::Activate()
{
	for (int i = 0; i < Data.Num(); i++)
	{
		if (Data[i].MeshComponent) {
			Data[i].MeshComponent->SetMaterial(Data[i].MaterialIndex, Data[i].ChangedMaterial);
		} else LOG_WARNING("[%s] MeshComponent not found for %s", *GetName(), *Data[i].MeshComponentName.ToString());
	}
	//Mesh->SetMaterial(MaterialIndex, ChangedMaterial);
}

void AAberrationMaterial::Deactivate()
{
	for (int i = 0; i < Data.Num(); i++)
	{
		if (Data[i].MeshComponent) {
			Data[i].MeshComponent->SetMaterial(Data[i].MaterialIndex, Data[i].DefaultMaterial);
		} else LOG_WARNING("[%s] MeshComponent not found for %s", *GetName(), *Data[i].MeshComponentName.ToString());
	}
	
	//Mesh->SetMaterial(MaterialIndex, DefaultMaterial);
}