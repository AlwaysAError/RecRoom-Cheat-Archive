#pragma once
#include <Windows.h>
#include <MinHook.h>
#include "xorstr.hpp"
#include <string.h>
#include <string>
#include "vector"
#include "natives.h"
#include "../includes.h"
#include "../logger.h"


struct System_String_o {
	void* klass;
	void* monitor;
	void* bounds;
	int length;
	wchar_t chars[1];
};

std::string ConvertIl2cppString(System_String_o* str) {
	if (!str) return "[null]";
	std::wstring ws(str->chars, str->length);
	return std::string(ws.begin(), ws.end()); // Simple conversion (lossy but who cares)
}

//System_String$$CreateString
std::string* CreateString(const char* str)
{
	static std::string* (*Create)(void* instance, const char* str, int* startIndex, int* length) =
		(std::string * (*)(void*, const char* str, int* startIndex, int* length))reinterpret_cast<void**>(ModuleGA + (0x2C48800));
	return Create(NULL, str, 0, (int*)strlen(str));
}

//RecRoom_Consumable_ConsumableManager$$SpawnConsumableForLocalPlayer
void (*SpawnConsumableForLocalPlayer_O)(DWORD*, std::string*, unsigned long*, Vector3, Quaternion, float, INT32*, DWORD*);
void SpawnConsumableForLocalPlayer_H(DWORD* __this, std::string* string, unsigned long* longPrt, Vector3 Vec, Quaternion quat, float scale, INT32* BFDCKEJIDML, DWORD* method)
{
	if (UI::FoodExploit::FoodSwap)
	{
		int foodcount = UI::FoodExploit::FoodInt;
		for (int i = 0; i < foodcount - 1; ++i)
		{
			SpawnConsumableForLocalPlayer_O(__this, CreateString(SelectedFood), longPrt, Vec, quat, UI::FoodExploit::FoodScale, BFDCKEJIDML, method);
		}
		SpawnConsumableForLocalPlayer_O(__this, CreateString(SelectedFood), longPrt, Vec, quat, UI::FoodExploit::FoodScale, BFDCKEJIDML, method);
	}
	else
	{

		SpawnConsumableForLocalPlayer_O(__this, string, longPrt, Vec, quat, UI::FoodExploit::FoodScale, BFDCKEJIDML, method);
	}
}




//RecRoom_Core_Locomotion_PlayerMovement$$get_IsFlyingEnabled
bool(*get_IsFlyingEnabled_o)(DWORD*, DWORD*);
bool get_isFlyingEnabled_h(DWORD* leck, DWORD* eier)
{
	if (UI::Movement::DynamicFly)

		return true;

	else

		return get_IsFlyingEnabled_o(leck, eier);

}




//RecRoom_Core_Locomotion_PlayerMovement$$AddFlyEnabled
void (*AddFlyEnabled_o)(DWORD*, bool, DWORD*, INT32, DWORD*);
void  AddFlyEnabled_h(DWORD* __this, bool enable, DWORD* token, INT32 priority, DWORD* method)
{
	if (UI::Movement::StaticFly)
		return AddFlyEnabled_o(__this, 1, token, 1, method);
	else
		return AddFlyEnabled_o(__this, enable, token, priority, method);

}



//RecRoom_Systems_PlayerRoles_PlayerRoomRoleManager$$get_LocalPlayerCanUseCreationMode
bool(*LocalPlayerCanUseCreationMode_o)(DWORD*);
bool LocalPlayerCanUseCreationMode_h(DWORD* method)
{
	if (UI::MakerPen::MakerPen)
		return true;
	else
		return LocalPlayerCanUseCreationMode_o(method);

}

//RecRoom_Avatars_Data_Runtime_AvatarItemSelection$$get_IsItemUnlockedLocally
bool (*get_IsItemUnlockedLocally_o)(DWORD*, DWORD*);
bool get_IsItemUnlockedLocally_h(DWORD* __this, DWORD* method)
{
	if (UI::Wardrobe::ItemUnlocker)
		return true;
	else
		return get_IsItemUnlockedLocally_o(__this, method);
}

//GameCombatManager$$PlayerIsInvincible     // Quest godmode
bool (*QuestInvincible_o)(DWORD*, DWORD*);
bool QuestInvincible_h(DWORD* __this, DWORD* method)
{
	if (UI::Health::QuestGodmode)
		return true;
	else
		return QuestInvincible_o(__this, method);
}

//RecRoom_Systems_PlayerRoles_PlayerRoomRoleManager$$get_LocalPlayerCanSpawnInvention
bool (*LocalPlayerCanSpawnInvention_o)(DWORD*);
bool LocalPlayerCanSpawnInvention_h(DWORD* method)
{
	if (UI::MakerPen::SpawnInvention)
		return true;
	else
		return LocalPlayerCanSpawnInvention_o(method);
}

//SessionManager$$get_IsDeveloper
bool(*Get_IsDeveloper_o)(DWORD*);
bool Get_IsDeveloper_h(DWORD* method)
{
	if (UI::DeveloperUI::developer)
		return true;
	else
		return Get_IsDeveloper_o(method);
}

//RecRoom_Activities_Quest_QuestManager$$RpcMasterAwardPoints
void(*RpcMasterAwardPoints_O)(DWORD*, Vector3, DWORD*, int32_t, bool, int32_t, bool, DWORD*);
void RpcMasterAwardPoints_H(DWORD* __this, Vector3 Vec, DWORD* AHHJCLLDIPM, int32_t int1, bool bool1, int32_t int2, bool bool2, DWORD* method)
{
	if (UI::Quests::Points::QuestPointsModifier)
		return RpcMasterAwardPoints_O(__this, Vec, AHHJCLLDIPM, UI::Quests::Points::QuestPointsInt, bool1, UI::Quests::Points::QuestPointsInt, bool2, method);
	else
		return RpcMasterAwardPoints_O(__this, Vec, AHHJCLLDIPM, int1, bool1, int2, bool2, method);
}


//RecRoom_Core_GameManagement_LootManager$$RpcMasterRequestAddLootAllPlayers
void(*RpcMasterRequestAddLootAllPlayers_O)(DWORD*, DWORD*, DWORD*, INT32, DWORD*);
void RpcMasterRequestAddLootAllPlayers_H(DWORD* __this, DWORD* method, DWORD* tygYUH, INT32 Intt, DWORD* wdawd)
{
	if (UI::Quests::Points::QuestGoldModifier)
		return RpcMasterRequestAddLootAllPlayers_O(__this, method, tygYUH, UI::Quests::Points::QuestGoldInt, wdawd);
	else
		return RpcMasterRequestAddLootAllPlayers_O(__this, method, tygYUH, Intt, wdawd);
}

//RecRoom_Activities_Quest_QuestManager$$GetCurrentGameplayRoomIndex
INT32(*GetCurrentGameplayRoomIndex_O)(DWORD*, DWORD*);
INT32 GetCurrentGameplayRoomIndex_H(DWORD* __this, DWORD* method)
{
	if (UI::Quests::Skip::SkipGoldenTrophy) { return INT32(9); }
	else if (UI::Quests::Skip::SkipCrims) { return INT32(9); }
	else if (UI::Quests::Skip::SkipJumbotron) { return INT32(9); }
	else if (UI::Quests::Skip::SkipIsle) { return INT32(7); }
	else if (UI::Quests::Skip::SkipCresendo) { return INT32(12); }
	else if (UI::Quests::Skip::SkipBoss) { return INT32(99); }
	else if (UI::Quests::Skip::CustomSkip) { return INT32(UI::Quests::Skip::CustomSkipper); }
	else
		return GetCurrentGameplayRoomIndex_O(__this, method);
}

//RecRoom_Core_Combat_RangedWeapon$$get_IsOnCooldown
bool(*get_IsOnCooldown_O)(DWORD*, DWORD*);
bool get_IsOnCooldown_H(DWORD* __this, DWORD* method)
{
	if (UI::Weapon::NoCoolDown)
		return false;
	else
		return get_IsOnCooldown_O(__this, method);
}

//GameCombatManager$$RpcMasterRequestSelfRevive
void(*RpcMasterRequestSelfRevive_O)(DWORD*, bool, DWORD*);
void RpcMasterRequestSelfRevive_H(DWORD* __this, bool permsig, DWORD* method)
{
	if (UI::Health::SelfRevive)
		return RpcMasterRequestSelfRevive_O(__this, 1, method);
	else
		return RpcMasterRequestSelfRevive_O(__this, permsig, method);
}

//Player$$SetHeadScale
void (*set_HeadScale_O)(DWORD*, float, DWORD*);
void set_HeadScale_H(DWORD* __this, float scale, DWORD* method)
{
	if (UI::Player::Head::HeadScaling)
		return set_HeadScale_O(__this, UI::Player::Head::HScale, method);
	else
		return set_HeadScale_O(__this, scale, method);
}


//RecRoom_Core_Combat_Weapon$$ForceAmmunitionValuesOnSpawn
void(*Set_Ammunition_O)(DWORD*, int32_t, int32_t, DWORD*);
void Set_Ammunition_H(DWORD* __this, int32_t velocity, int32_t charge, DWORD* ZaZa)
{
	if (UI::Weapon::InfiniteAmmo)
		return Set_Ammunition_O(__this, 1, 1, ZaZa);
	else
		return Set_Ammunition_O(__this, velocity, charge, ZaZa);
}

//RecRoom_Core_Combat_RangedWeapon$$Fire_6455715312
//void(*Fire_O)(DWORD*, Vector3, float, DWORD*);
//void Fire_H(DWORD* __this, Vector3 velocity, float charge, DWORD* Parkbank)
//{
//	int Bullets = UI::BulletModifiers::BulletAmount;
//	for (int i = 0; i < Bullets - 1; ++i)
//	{
//		Fire_O(__this, velocity, charge, Parkbank);
//	}
//	return Fire_O(__this, velocity, charge, Parkbank);
//}

//UnityEngine_Camera$$set_fieldOfView
void (*SetFOV_O)(DWORD*, float, DWORD*);
void SetFOV_H(DWORD* __this, float fov, DWORD* method)
{
	if (UI::Engine::FOV)
		return SetFOV_O(__this, UI::Engine::PlayerFOV, method);
	else
		return SetFOV_O(__this, fov, method);
}

//RecRoom_Core_Creation_CreationManager$$get_IsOverInkLimit
bool (*IsOverInkLimit_O)(DWORD*, DWORD*);
bool IsOverInkLimit_H(DWORD* __this, DWORD* method)
{
	if (UI::MakerPen::InkLimit)
		return false;
	else
		return IsOverInkLimit_O(__this, method);
}


//
//Player$$set_DeveloperDisplayMode
void (*set_DeveloperDisplayMode_O)(DWORD*, INT32, DWORD*);
void set_DeveloperDisplayMode_H(DWORD* __this, INT32 mode, DWORD* method)
{
	if (UI::DeveloperUI::developer)
		return set_DeveloperDisplayMode_O(__this, 1, method);
	else
		return set_DeveloperDisplayMode_O(__this, mode, method);
}

bool (*get_IsTrialItem_O)(DWORD*, DWORD*);
bool get_IsTrialItem_H(DWORD* __this, DWORD* method)
{
	if (UI::Wardrobe::ItemUnlocker)
		return false;
	else
		return get_IsTrialItem_O(__this, method);
}


//UnityEngine_Time$$set_timeScale
void (*set_timeScale_O)(float, DWORD*);
void set_timeScale_H(float time, DWORD* method)
{
	if (UI::Engine::TimeScale)
		return set_timeScale_O(UI::Engine::TimeFloat, method);
	else
		return set_timeScale_O(time, method);
}

float (*get_timeScale_O)(DWORD*);
float get_timeScale_H(DWORD* method)
{
	if (UI::Engine::TimeScale)
		return UI::Engine::TimeFloat;
	else
		return get_timeScale_O(method);
}

bool (*Airstuck_O)(DWORD*, DWORD*);
bool Airstuck_H(DWORD* __this, DWORD* method) // Airstuck exploit prob the first exploit in this game not gonna lie im not caring enough to make it better and im not gonna name it so people dont steal it :D
{
	if (UI::Engine::Airstuck)
		return false;
	else
		return Airstuck_O(__this, method);
}

void (*MasterKill_O)(DWORD*, DWORD*);
void MasterKill_H(DWORD* pntr, DWORD* method)
{
	if (UI::Engine::MasterKill)
		return MasterKill_O(pntr, method);
}

void (*MasterDispose_O)(DWORD*, DWORD*);
void MasterDispose_H(DWORD* pntr, DWORD* method)
{
	if (UI::Engine::MasterKill)
		return MasterDispose_O(pntr, method);
}

bool (*get_isAlive_O)(DWORD*, DWORD*);
bool get_isAlive_H(DWORD* real, DWORD* method)
{
	if (UI::Engine::MasterKill)
		return false;
	else
		return get_isAlive_O(real, method);
}

void (*set_EnemyHealth_O)(DWORD*, INT32, DWORD*);
void set_EnemyHealth_H(DWORD* pussy, INT32 int1, DWORD* method)
{
	if (UI::Engine::MasterKill)
		return set_EnemyHealth_O(pussy, 0, method);
	else
		return set_EnemyHealth_O(pussy, int1, method);
}



void (*AIController_Set_Health_O)(DWORD*, INT32, DWORD*);
void AIController_Set_Health_H(DWORD* penis, INT32 health, DWORD* method)
{
	if (UI::Engine::MasterKill)
		return AIController_Set_Health_O(penis, 0, method);
	else
		return AIController_Set_Health_O(penis, health, method);
}
void (*JUMBOSS_set_health_O)(DWORD*, INT32, DWORD*);
void JUMBOSS_set_health_H(DWORD* penis, INT32 health, DWORD* method)
{
	if (UI::Engine::MasterKill)
		return AIController_Set_Health_O(penis, 0, method);
	else
		return AIController_Set_Health_O(penis, health, method);
}

bool (*IsAvatarItemAlreadyPurchased_O)(DWORD*, DWORD*, DWORD*);
bool IsAvatarItemAlreadyPurchased_H(DWORD* pussy, DWORD* nigga, DWORD* method)
{
	if (UI::Wardrobe::ItemUnlocker)
		return true;
	else
		return IsAvatarItemAlreadyPurchased_O(pussy, nigga, method);
}

bool (*IsAvatarItemUnlocked_O)(DWORD*, DWORD*, DWORD*);
bool IsAvatarItemUnlocked_H(DWORD* pussy, DWORD* black, DWORD* method)
{
	if (UI::Wardrobe::ItemUnlocker)
		return true;
	else
		return IsAvatarItemAlreadyPurchased_O(pussy, black, method);
}

float (*UnityCamera_Aspect_O)(DWORD*, DWORD*);
float UnityCamera_Aspect_H(DWORD* asi, DWORD* method) //doesnt work, and shouldnt work cs fuck this 5/2/2021
{
	if (UI::Engine::aspectRation)
		return UI::Engine::floataspect;
	else
		return UnityCamera_Aspect_O(asi, method);
}

void Hooks() //No Im Not Gonna Use Patterns cs We are not Gonna rely on it you fucking dumbass
{
	Log::log("Hooks Are Working Please Wait :D");
	MH_Initialize();


	/*                                         Rec Room Functions                                         */
	MH_CreateHook(reinterpret_cast<void**>(ModuleGA + (0xF09930)), &get_isFlyingEnabled_h, (void**)&get_IsFlyingEnabled_o);
	MH_EnableHook(reinterpret_cast<void**>(ModuleGA + (0xF09930)));

	MH_CreateHook(reinterpret_cast<void**>(ModuleGA + (0xEFC980)), &AddFlyEnabled_h, (void**)&AddFlyEnabled_o);
	MH_EnableHook(reinterpret_cast<void**>(ModuleGA + (0xEFC980)));

	MH_CreateHook(reinterpret_cast<void**>(ModuleGA + (0x976A60)), &LocalPlayerCanUseCreationMode_h, (void**)&LocalPlayerCanUseCreationMode_o);
	MH_EnableHook(reinterpret_cast<void**>(ModuleGA + (0x976A60)));

	MH_CreateHook(reinterpret_cast<void**>(ModuleGA + (0x11D3FD0)), &get_IsItemUnlockedLocally_h, (void**)&get_IsItemUnlockedLocally_o);
	MH_EnableHook(reinterpret_cast<void**>(ModuleGA + (0x11D3FD0)));

	MH_CreateHook(reinterpret_cast<void**>(ModuleGA + (0x9768E0)), &LocalPlayerCanSpawnInvention_h, (void**)&LocalPlayerCanSpawnInvention_o);
	MH_EnableHook(reinterpret_cast<void**>(ModuleGA + (0x9768E0)));

	MH_CreateHook(reinterpret_cast<void**>(ModuleGA + (0xA552F0)), &Get_IsDeveloper_h, (void**)&Get_IsDeveloper_o);
	MH_EnableHook(reinterpret_cast<void**>(ModuleGA + (0xA552F0)));

	MH_CreateHook(reinterpret_cast<void**>(ModuleGA + (0xCA8CA0)), &get_IsOnCooldown_H, (void**)&get_IsOnCooldown_O);
	MH_EnableHook(reinterpret_cast<void**>(ModuleGA + (0xCA8CA0)));

	MH_CreateHook(reinterpret_cast<void**>(ModuleGA + (0x12031E0)), &SpawnConsumableForLocalPlayer_H, (void**)&SpawnConsumableForLocalPlayer_O);
	MH_EnableHook(reinterpret_cast<void**>(ModuleGA + (0x12031E0)));

	MH_CreateHook(reinterpret_cast<void**>(ModuleGA + (0xCAE4C0)), &Set_Ammunition_H, (void**)&Set_Ammunition_O);
	MH_EnableHook(reinterpret_cast<void**>(ModuleGA + (0xCAE4C0)));

	MH_CreateHook(reinterpret_cast<void**>(ModuleGA + (0xC93840)), &IsOverInkLimit_H, (void**)&IsOverInkLimit_O);
	MH_EnableHook(reinterpret_cast<void**>(ModuleGA + (0xC93840)));

	MH_CreateHook(reinterpret_cast<void**>(ModuleGA + (0x8381A0)), &set_DeveloperDisplayMode_H, (void**)&set_DeveloperDisplayMode_O);
	MH_EnableHook(reinterpret_cast<void**>(ModuleGA + (0x8381A0)));

	MH_CreateHook(reinterpret_cast<void**>(ModuleGA + (0x11DDA20)), &IsAvatarItemAlreadyPurchased_H, (void**)&IsAvatarItemAlreadyPurchased_O);
	MH_EnableHook(reinterpret_cast<void**>(ModuleGA + (0x11DDA20)));

	MH_CreateHook(reinterpret_cast<void**>(ModuleGA + (0x11DDAD0)), &IsAvatarItemUnlocked_H, (void**)&IsAvatarItemUnlocked_O);
	MH_EnableHook(reinterpret_cast<void**>(ModuleGA + (0x11DDAD0)));
	/*                                         Rec Room Functions                                         */



	/*                                              Movement                                              */
	MH_CreateHook(reinterpret_cast<void**>(ModuleGA + (0x460D40)), &Airstuck_H, (void**)&Airstuck_O);
	MH_EnableHook(reinterpret_cast<void**>(ModuleGA + (0x460D40)));
	/*                                              Movement                                              */



	/*                                            Unity Engine                                            */
	MH_CreateHook(reinterpret_cast<void**>(ModuleGA + (0x2E20320)), &SetFOV_H, (void**)&SetFOV_O);
	MH_EnableHook(reinterpret_cast<void**>(ModuleGA + (0x2E20320)));

	MH_CreateHook(reinterpret_cast<void**>(ModuleGA + (0x2E1F3C0)), &UnityCamera_Aspect_H, (void**)&UnityCamera_Aspect_O);
	MH_EnableHook(reinterpret_cast<void**>(ModuleGA + (0x2E1F3C0)));

	MH_CreateHook(reinterpret_cast<void**>(ModuleGA + (0x30118C0)), &set_timeScale_H, (void**)&set_timeScale_O);
	MH_EnableHook(reinterpret_cast<void**>(ModuleGA + (0x30118C0)));

	MH_CreateHook(reinterpret_cast<void**>(ModuleGA + (0x833E50)), &set_HeadScale_H, (void**)&set_HeadScale_O);
	MH_EnableHook(reinterpret_cast<void**>(ModuleGA + (0x833E50)));

	MH_CreateHook(reinterpret_cast<void**>(ModuleGA + (0x30116F0)), &get_timeScale_H, (void**)&get_timeScale_O);
	MH_EnableHook(reinterpret_cast<void**>(ModuleGA + (0x30116F0)));
	/*                                            Unity Engine                                            */



	/*                                            Quest Related                                            */
	MH_CreateHook(reinterpret_cast<void**>(ModuleGA + (0xE20180)), &QuestInvincible_h, (void**)&QuestInvincible_o);
	MH_EnableHook(reinterpret_cast<void**>(ModuleGA + (0xE20180)));

	MH_CreateHook(reinterpret_cast<void**>(ModuleGA + (0x1588C50)), &RpcMasterAwardPoints_H, (void**)&RpcMasterAwardPoints_O);
	MH_EnableHook(reinterpret_cast<void**>(ModuleGA + (0x1588C50)));

	MH_CreateHook(reinterpret_cast<void**>(ModuleGA + (0xA302F0)), &RpcMasterRequestAddLootAllPlayers_H, (void**)&RpcMasterRequestAddLootAllPlayers_O);
	MH_EnableHook(reinterpret_cast<void**>(ModuleGA + (0xA302F0)));

	MH_CreateHook(reinterpret_cast<void**>(ModuleGA + (0x1584640)), &GetCurrentGameplayRoomIndex_H, (void**)&GetCurrentGameplayRoomIndex_O);
	MH_EnableHook(reinterpret_cast<void**>(ModuleGA + (0x1584640)));

	MH_CreateHook(reinterpret_cast<void**>(ModuleGA + (0xE21950)), &RpcMasterRequestSelfRevive_H, (void**)&RpcMasterRequestSelfRevive_O);
	MH_EnableHook(reinterpret_cast<void**>(ModuleGA + (0xE21950)));


	MH_CreateHook(reinterpret_cast<void**>(ModuleGA + (0x1394700)), &MasterKill_H, (void**)&MasterKill_O);
	MH_EnableHook(reinterpret_cast<void**>(ModuleGA + (0x1394700)));

	MH_CreateHook(reinterpret_cast<void**>(ModuleGA + (0x13945D0)), &MasterDispose_H, (void**)&MasterDispose_O);
	MH_EnableHook(reinterpret_cast<void**>(ModuleGA + (0x13945D0)));

	MH_CreateHook(reinterpret_cast<void**>(ModuleGA + (0x139A280)), &get_isAlive_H, (void**)&get_isAlive_O);
	MH_EnableHook(reinterpret_cast<void**>(ModuleGA + (0x139A280)));

	MH_CreateHook(reinterpret_cast<void**>(ModuleGA + (0x139B250)), &set_EnemyHealth_H, (void**)&set_EnemyHealth_O);
	MH_EnableHook(reinterpret_cast<void**>(ModuleGA + (0x139B250)));

	MH_CreateHook(reinterpret_cast<void**>(ModuleGA + (0xCA18E0)), &AIController_Set_Health_H, (void**)&AIController_Set_Health_O);
	MH_EnableHook(reinterpret_cast<void**>(ModuleGA + (0xCA18E0)));

	MH_CreateHook(reinterpret_cast<void**>(ModuleGA + (0x157C3A0)), &JUMBOSS_set_health_H, (void**)&JUMBOSS_set_health_O);
	MH_EnableHook(reinterpret_cast<void**>(ModuleGA + (0x157C3A0)));

	/*                                            Quest Related                                            */



	/*                                            ANACD Related                                            */


	/*                                            ANACD Related                                            */

	//MH_CreateHook(reinterpret_cast<void**>(ModuleGA + (0x8378C0)), &get_PlayerName_H, (void**)&get_PlayerName_O);
	//MH_EnableHook(reinterpret_cast<void**>(ModuleGA + (0x8378C0)));



	Log::log("Hooks Are Done");
}
