// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ProjectCotD/ProjectCotDGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeProjectCotDGameMode() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
PROJECTCOTD_API UClass* Z_Construct_UClass_AProjectCotDGameMode();
PROJECTCOTD_API UClass* Z_Construct_UClass_AProjectCotDGameMode_NoRegister();
UPackage* Z_Construct_UPackage__Script_ProjectCotD();
// End Cross Module References

// Begin Class AProjectCotDGameMode
void AProjectCotDGameMode::StaticRegisterNativesAProjectCotDGameMode()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AProjectCotDGameMode);
UClass* Z_Construct_UClass_AProjectCotDGameMode_NoRegister()
{
	return AProjectCotDGameMode::StaticClass();
}
struct Z_Construct_UClass_AProjectCotDGameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "ProjectCotDGameMode.h" },
		{ "ModuleRelativePath", "ProjectCotDGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AProjectCotDGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AProjectCotDGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_ProjectCotD,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AProjectCotDGameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AProjectCotDGameMode_Statics::ClassParams = {
	&AProjectCotDGameMode::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x008802ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AProjectCotDGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_AProjectCotDGameMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AProjectCotDGameMode()
{
	if (!Z_Registration_Info_UClass_AProjectCotDGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AProjectCotDGameMode.OuterSingleton, Z_Construct_UClass_AProjectCotDGameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AProjectCotDGameMode.OuterSingleton;
}
template<> PROJECTCOTD_API UClass* StaticClass<AProjectCotDGameMode>()
{
	return AProjectCotDGameMode::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AProjectCotDGameMode);
AProjectCotDGameMode::~AProjectCotDGameMode() {}
// End Class AProjectCotDGameMode

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_totof_Documents_Work_vertical_Project_CotD_ProjectCotD_Source_ProjectCotD_ProjectCotDGameMode_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AProjectCotDGameMode, AProjectCotDGameMode::StaticClass, TEXT("AProjectCotDGameMode"), &Z_Registration_Info_UClass_AProjectCotDGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AProjectCotDGameMode), 1394494732U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_totof_Documents_Work_vertical_Project_CotD_ProjectCotD_Source_ProjectCotD_ProjectCotDGameMode_h_2810975937(TEXT("/Script/ProjectCotD"),
	Z_CompiledInDeferFile_FID_Users_totof_Documents_Work_vertical_Project_CotD_ProjectCotD_Source_ProjectCotD_ProjectCotDGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_totof_Documents_Work_vertical_Project_CotD_ProjectCotD_Source_ProjectCotD_ProjectCotDGameMode_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
