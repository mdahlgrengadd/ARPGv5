// Copyright Epic Games, Inc. All Rights Reserved.

#include "RPG_GASP_Combined.h"

#define LOCTEXT_NAMESPACE "FRPG_GASP_CombinedModule"

void FRPG_GASP_CombinedModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FRPG_GASP_CombinedModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FRPG_GASP_CombinedModule, RPG_GASP_Combined)