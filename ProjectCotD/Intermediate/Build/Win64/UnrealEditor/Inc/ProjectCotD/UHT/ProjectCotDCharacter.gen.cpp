// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ProjectCotD/ProjectCotDCharacter.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeProjectCotDCharacter() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_ACharacter();
PROJECTCOTD_API UClass* Z_Construct_UClass_AProjectCotDCharacter();
PROJECTCOTD_API UClass* Z_Construct_UClass_AProjectCotDCharacter_NoRegister();
UPackage* Z_Construct_UPackage__Script_ProjectCotD();
// End Cross Module References

// Begin Class AProjectCotDCharacter
void AProjectCotDCharacter::StaticRegisterNativesAProjectCotDCharacter()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AProjectCotDCharacter);
UClass* Z_Construct_UClass_AProjectCotDCharacter_NoRegister()
{
	return AProjectCotDCharacter::StaticClass();
}
struct Z_Construct_UClass_AProjectCotDCharacter_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "ProjectCotDCharacter.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "ProjectCotDCharacter.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AProjectCotDCharacter>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AProjectCotDCharacter_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ACharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_ProjectCotD,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AProjectCotDCharacter_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AProjectCotDCharacter_Statics::ClassParams = {
	&AProjectCotDCharacter::StaticClass,
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
	0x008000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AProjectCotDCharacter_Statics::Class_MetaDataParams), Z_Construct_UClass_AProjectCotDCharacter_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AProjectCotDCharacter()
{
	if (!Z_Registration_Info_UClass_AProjectCotDCharacter.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AProjectCotDCharacter.OuterSingleton, Z_Construct_UClass_AProjectCotDCharacter_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AProjectCotDCharacter.OuterSingleton;
}
template<> PROJECTCOTD_API UClass* StaticClass<AProjectCotDCharacter>()
{
	return AProjectCotDCharacter::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AProjectCotDCharacter);
AProjectCotDCharacter::~AProjectCotDCharacter() {}
// End Class AProjectCotDCharacter

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_totof_Documents_Work_vertical_Project_CotD_ProjectCotD_Source_ProjectCotD_ProjectCotDCharacter_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AProjectCotDCharacter, AProjectCotDCharacter::StaticClass, TEXT("AProjectCotDCharacter"), &Z_Registration_Info_UClass_AProjectCotDCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AProjectCotDCharacter), 3653986616U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_totof_Documents_Work_vertical_Project_CotD_ProjectCotD_Source_ProjectCotD_ProjectCotDCharacter_h_4063802385(TEXT("/Script/ProjectCotD"),
	Z_CompiledInDeferFile_FID_Users_totof_Documents_Work_vertical_Project_CotD_ProjectCotD_Source_ProjectCotD_ProjectCotDCharacter_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_totof_Documents_Work_vertical_Project_CotD_ProjectCotD_Source_ProjectCotD_ProjectCotDCharacter_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
