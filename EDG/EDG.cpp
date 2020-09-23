#include "stdafx.h"
#include "LandTableInfo.h"
#include "SA2ModLoader.h"
#include "IniFile.h"
#include "TextConv.h"
#include "EDGResources.h"

#define ReplaceSET(a, b) helperFunctions.ReplaceFile("resource\\gd_PC\\" a ".bin", "resource\\gd_PC\\" b ".bin");

extern "C"
{

	NJS_VECTOR dTransporterPos = { 123.27f , -0.1f + 2.0f , 122.27f };

	void TransporterLoadingDark()
	{
		NJS_VECTOR position;
		position.x = dTransporterPos.x;
		position.y = -0.1f;
		position.z = dTransporterPos.y;
		Transporter_Load(&position, 24940);
	}

	NJS_TEXNAME eDarkTexCount[18];
	NJS_TEXLIST eDarkTexList = { arrayptrandlength(eDarkTexCount) };

	__declspec(dllexport) void Init(const char* path, const HelperFunctions& helperFunctions)
	{
		HMODULE hmodule = GetModuleHandle(__TEXT("Data_DLL_orig"));

		WriteCall((void*)0x0052B408, nullsub_1); //Disables Height
		WriteCall((void*)0x0052B430, nullsub_1);

		const IniFile* config = new IniFile(std::string(path) + "\\config.ini");

		WriteData((float**)0x0052B970, &dTransporterPos.x);
		WriteData((float**)0x0052B978, &dTransporterPos.y);
		WriteData((float**)0x0052B981, &dTransporterPos.z);
		WriteCall((void*)0x0054D3F4, TransporterLoadingDark);

		ReplaceSET("set_chao_dark_s", "set_chao_edark_s")

		bool Set = config->getBool("GenSet", "Set", false);
		if (!Set)
		{
			ReplaceSET("set_chao_dark_u", "set_null")
		}

		bool toys = config->getBool("GenSet", "Toys", true);
		if (toys)
		{
			//WriteCall((void*)0x0054D490, sALO_Horse_Load);
			//WriteData((int*)0x00580F80, heroHorseRot);
			//WriteCall((void*)0x0054D44B, hALO_Ball_Load); //Toys
		}

		((NJS_TEXLIST*)GetDllData("texlist_al_stg_dark_tex"))->textures = eDarkTexCount;

		LandTable* DarkTable = (LandTable*)GetDllData("objLandTableDark");
		NJS_OBJECT* BloodSpring = (NJS_OBJECT*)GetDllData("object_gdark_nc_hotspring00_hotspring00");

		LandTable* EDark = (LandTable*)GetProcAddress(hmodule, "objLandTableDark");
		*EDark = *(new LandTableInfo(std::string(path) + "\\Landtables\\EDark.sa2blvl"))->getlandtable();
		EDark->TextureList = &eDarkTexList;
		EDark->TextureName = (char*)"al_stg_dark_tex";

		NJS_OBJECT* EBloodSpring = EDark->COLList[0].Model;

		EDark->COLList[0].Flags &= ~0x80000000;

		*BloodSpring = *EBloodSpring;

		DataArray(NJS_VECTOR, ChaoPos, 0x01366260, 16 * 3);

		ChaoPos[33] = { 0, 20, 0 };             
		ChaoPos[34] = { 0, 20, 0 };                      
		ChaoPos[35] = { 0, 20, 0 };           
		ChaoPos[36] = { 0, 20, 0 };           
		ChaoPos[37] = { 0, 20, 0 };           
		ChaoPos[38] = { 0, 20, 0 };                
		ChaoPos[39] = { 0, 20, 0 };                
		ChaoPos[40] = { 0, 20, 0 };              
		ChaoPos[41] = { 0, 20, 0 };                 
		ChaoPos[42] = { 0, 20, 0 };            
		ChaoPos[43] = { 0, 20, 0 };            
		ChaoPos[44] = { 0, 20, 0 };            
		ChaoPos[45] = { 0, 20, 0 };               
		ChaoPos[46] = { 0, 20, 0 };             
		ChaoPos[47] = { 0, 20, 0 };               
		ChaoPos[48] = { 0, 20, 0 };          

		DataArray(NJS_VECTOR, TreePos, 0x01366B30, 30);

		TreePos[17] = { -104.69f, 1, 10.15f };               // Normal Tree 1 
		TreePos[18] = { 89.11f, 1, 63.58f };                 // Normal Tree 2
		TreePos[19] = { -114.68f, 15.58f, -111.89f };        // Normal Tree 3 
		TreePos[20] = { -28.98f, 1, -6.37f };                // Custom Tree 1 
		TreePos[21] = { -30.15f, 15.15f, -126.83f };         // Custom Tree 2
		TreePos[22] = { 54.57f, 1, 109.94f };                // Custom Tree 3
		TreePos[23] = { 82.21f, 1, 9.123f };                 // Custom Tree 4

	}

	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}