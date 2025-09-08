#pragma once
#include "Windows.h"
#include "..\globals\globals.h"
#include "..\IL2CPP_Resolver.hpp"
#include <math.h>
#include <random>
#include <unordered_map>
#include <string>
#include <iostream>
#include <thread>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


struct Vector3 {
	float x;
	float y;
	float z;
};

struct Quaternion {
	float x;
	float y;
	float z;
	float w;
};


bool(*get_IsFlyingEnabled_o)(DWORD*, DWORD*);
bool get_isFlyingEnabled_h(DWORD* leck, DWORD* eier)
{
	if (globals::movement::dynamicfly)
		

		return true;

	else

		return get_IsFlyingEnabled_o(leck, eier);

}

bool(*get_IsOnCooldown_O)(DWORD*, DWORD*);
bool get_IsOnCooldown_H(DWORD* __this, DWORD* method)
{
	if (globals::combat::rapidfire)
		return false;
	else
		return get_IsOnCooldown_O(__this, method);
}

void (*RpcPlayLevelUpFeedback_O)(void* __this, void* MFAOJHBGOGK);
void RpcPlayLevelUpFeedback_H(void* __this, void* MFAOJHBGOGK) {

	// Print the addresses of the two parameters
	printf("__this address: %p\n", __this);
	printf("MFAOJHBGOGK address: %p\n", MFAOJHBGOGK);

	if (globals::network::disableramcrashcheer)
	{
		RpcPlayLevelUpFeedback_O(__this, __this);
	}
	else
	{
		RpcPlayLevelUpFeedback_O(__this, MFAOJHBGOGK);
	}
}

void* (*CV2ShowBannerNotification_O)(	void* __this,	void* DNLEOFNAGNA,	void* FLAPAOJCDCM,	float DFOOIFEDPMI,	void* GBBEGJGJHAK,	void* DOFECHCNEMF,	void* HKDLOKFCGPH,	void* MFCJPJJBEPC,	void* PPBBDDFNDEG,	void* GDIAECLNHFM,	void* FIDEOLAOPKB,	void* DNBHCOODLKO,	void* FANKEFMNPNG,	void* GLFJMLHOBOK	);

// Hooked function
void* CV2ShowBannerNotification_H(	void* __this,	void* DNLEOFNAGNA,	void* FLAPAOJCDCM,	float DFOOIFEDPMI,	void* GBBEGJGJHAK,	void* DOFECHCNEMF,	void* HKDLOKFCGPH,	void* MFCJPJJBEPC,	void* PPBBDDFNDEG,	void* GDIAECLNHFM,	void* FIDEOLAOPKB,	void* DNBHCOODLKO,	void* FANKEFMNPNG,	void* GLFJMLHOBOK) {
	if (globals::network::disablebannercv2)
	{
		printf("[+] Protected You From A Banner Notification\n");

		void* emptyString = nullptr;

		return CV2ShowBannerNotification_O(
			__this,
			DNLEOFNAGNA,
			FLAPAOJCDCM,
			DFOOIFEDPMI,
			emptyString,
			DOFECHCNEMF,
			HKDLOKFCGPH,
			MFCJPJJBEPC,
			emptyString,
			GDIAECLNHFM,
			FIDEOLAOPKB,
			DNBHCOODLKO,
			emptyString,
			emptyString
		);
	}
	else
	{

		return CV2ShowBannerNotification_O(
			__this,
			DNLEOFNAGNA,
			FLAPAOJCDCM,
			DFOOIFEDPMI,
			GBBEGJGJHAK,
			DOFECHCNEMF,
			HKDLOKFCGPH,
			MFCJPJJBEPC,
			PPBBDDFNDEG,
			GDIAECLNHFM,
			FIDEOLAOPKB,
			DNBHCOODLKO,
			FANKEFMNPNG,
			GLFJMLHOBOK
		);
	}
}

void* (*CV2GoToRoom_O)(void* __this, void* DNLEOFNAGNA, void* IFMFGPNJMBA);
void* CV2GoToRoom_H(void* __this, void* DNLEOFNAGNA, void* IFMFGPNJMBA)
{
	if (globals::network::disablegotoroom)
	{
		printf("[+] Protected You From Goto Room Event\n");

		return __this;
	}

	return CV2GoToRoom_O(__this, DNLEOFNAGNA, IFMFGPNJMBA);
}

void* (*CV2UnequipSlots_O)(void* __this, void* DNLEOFNAGNA, bool FKJKMJCCLHO, bool LJKCFKEGLBI, bool GFOFCEGMOJH, bool JJLFMDODNBE, bool AGEJDLEEKJB);
void* CV2UnequipSlots_H(void* __this, void* DNLEOFNAGNA, bool FKJKMJCCLHO, bool LJKCFKEGLBI, bool GFOFCEGMOJH, bool JJLFMDODNBE, bool AGEJDLEEKJB)

{
	if (globals::network::disableuneqipfromslots)
	{
		printf("[+] Protected You From Unequip Event\n");
		return CV2UnequipSlots_O(__this, DNLEOFNAGNA, false, false, false, false, false);
	}
	else
	{
		return CV2UnequipSlots_O(__this, DNLEOFNAGNA, FKJKMJCCLHO, LJKCFKEGLBI, GFOFCEGMOJH, JJLFMDODNBE, AGEJDLEEKJB);
	}

}

void (*set_eulerAngles_O)(DWORD* __this, Vector3 value, DWORD* method);

void set_eulerAngles_H(DWORD* __this, Vector3 value, DWORD* method)
{
	if (globals::player::spinbot)
	{
		static float yaw = 0.0f;
		yaw += 1.0f;
		if (yaw > 360.0f) yaw -= 360.0f;


		Vector3 spinAngles = { 0.0f, yaw, 0.0f };

		return set_eulerAngles_O(__this, spinAngles, method);
	}

	return set_eulerAngles_O(__this, value, method);
}

float (*get_CurrentProjectileSpeed_O)(DWORD*);
float get_CurrentProjectileSpeed_H(DWORD* __this)
{

	if (globals::combat::fastbullets)
		return 1000.0f;
	else
		return get_CurrentProjectileSpeed_O(__this);
}

bool (*IsAvatarItemAlreadyPurchased_O)(DWORD*, DWORD*, DWORD*);
bool IsAvatarItemAlreadyPurchased_H(DWORD* pussy, DWORD* nigga, DWORD* method)
{
	if (globals::inventory::clothing)
		return true;
	else
		return IsAvatarItemAlreadyPurchased_O(pussy, nigga, method);
}

bool (*IsAvatarItemUnlocked_O)(DWORD*, DWORD*, DWORD*);
bool IsAvatarItemUnlocked_H(DWORD* pussy, DWORD* black, DWORD* method)
{
	if (globals::inventory::clothing)
		return true;
	else
		return IsAvatarItemAlreadyPurchased_O(pussy, black, method);
}

float (*get_CurrentRecoilMultiplier_O)(DWORD*);
float get_CurrentRecoilMultiplier_H(DWORD* __this)
{
	// Example: force no recoil
	if (globals::combat::norecoil)
	{

		return 0.0f; // no recoil multiplier
	}


	// Otherwise, call original
	return get_CurrentRecoilMultiplier_O(__this);
}

bool (*get_IsTrialItem_O)(DWORD*, DWORD*);
bool get_IsTrialItem_H(DWORD* __this, DWORD* method)
{
	if (globals::inventory::clothing)
		return false;
	else
		return get_IsTrialItem_O(__this, method);
}

void(__fastcall* FOV_O)(DWORD*, float, DWORD*);
void __fastcall FOV_H(DWORD* __this, float value, DWORD* method)
{
	if (globals::player::fovtoggle)
	{
		return FOV_O(__this, globals::player::fov, method);
	}
	return FOV_O(__this, value, method);
}

DWORD* cached_this = nullptr;
DWORD* cached_parkbank = nullptr;

void(*Fire_O)(DWORD*, float, DWORD*);
void Fire_H(DWORD* __this, float charge, DWORD* Parkbank)
{
	cached_this = __this;
	cached_parkbank = Parkbank;
	int Bullets = globals::combat::buletamount;
	if (globals::combat::custombullet)
	{
		for (int i = 0; i < Bullets - 1; ++i)
		{
			Fire_O(__this, charge, Parkbank);
		}
	}

	return Fire_O(__this, charge, Parkbank);
}


void(*Set_Ammunition_O)(DWORD*, int32_t, int32_t, DWORD*);
void Set_Ammunition_H(DWORD* __this, int32_t velocity, int32_t charge, DWORD* ZaZa)
{
	if (globals::combat::infiniteammo)
		return Set_Ammunition_O(__this, 1, 1, ZaZa);
	else
		return Set_Ammunition_O(__this, velocity, charge, ZaZa);
}

bool(*Get_IsDeveloper_o)(DWORD*);
bool Get_IsDeveloper_h(DWORD* method)
{
	if (globals::player::developer)
		return true;
	else
		return Get_IsDeveloper_o(method);
}

bool(*get_CanUseShareCamera_o)(DWORD*);
bool get_CanUseShareCamera_h(DWORD* method)
{
	if (globals::inventory::sharecamera)
		return true;
	else
		return get_CanUseShareCamera_o(method);
}

bool(*get_CanUseStreamingCam_o)(DWORD*);
bool get_CanUseStreamingCam_h(DWORD* method)
{
	if (globals::inventory::steamercamera)
		return true;
	else
		return get_CanUseStreamingCam_o(method);
}

bool(*get_CanUseClothingCustomizer_o)(DWORD*);
bool get_CanUseClothingCustomizer_h(DWORD* method)
{
	if (globals::inventory::clothingcustomizer)
		return true;
	else
		return get_CanUseClothingCustomizer_o(method);
}

bool (*get_IsItemUnlockedLocally_o)(DWORD*, DWORD*);
bool get_IsItemUnlockedLocally_h(DWORD* __this, DWORD* method)
{
	if (globals::inventory::clothing)
		return true;
	else
		return get_IsItemUnlockedLocally_o(__this, method);
}

void (*AddFlyEnabled_o)(DWORD*, bool, DWORD*, INT32, DWORD*);
void  AddFlyEnabled_h(DWORD* __this, bool enable, DWORD* token, INT32 priority, DWORD* method)
{
	if (globals::movement::staticfly)
		return AddFlyEnabled_o(__this, 1, token, 1, method);
	else
		return AddFlyEnabled_o(__this, enable, token, priority, method);

}

bool (*old_DoesLocalPlayerOwnKeyG)(void* instance, void* guid);
bool DoesLocalPlayerOwnKeyG(void* instance, void* guid) {
	if (instance && globals::inventory::unlockkeys)
		return true;
	return old_DoesLocalPlayerOwnKeyG(instance, guid);
}

bool (*old_DoesLocalPlayerOwnKeyL)(void* instance, void* int64);
bool DoesLocalPlayerOwnKeyL(void* instance, void* int64) {
	if (instance && globals::inventory::unlockkeys)
		return true;
	return old_DoesLocalPlayerOwnKeyL(instance, int64);
}


using RpcFireShot_t = void(*)(void* __this, Vector3, Quaternion, Vector3, float, bool, uint8_t);
RpcFireShot_t RpcFireShot_O;

void RpcFireShot_H(
	void* __this,
	Vector3 position,
	Quaternion rotation,
	Vector3 velocity,
	float damage,
	bool someFlag,
	uint8_t extra
)
{
	// Anti-crash check
	if (globals::network::disableramcrashbullets)
		return;

	// "Crazy cool" multi-shot (3D cube)
	if (globals::combat::cubeofbullets)
	{
		const int cubeSize = 6;         // how many bullets along each axis
		const float spacing = 8.0f;     // distance between bullets
		const float halfExtent = (cubeSize - 1) * spacing * 0.5f; // center cube on original pos

		for (int x = 0; x < cubeSize; ++x)
		{
			for (int y = 0; y < cubeSize; ++y)
			{
				for (int z = 0; z < cubeSize; ++z)
				{
					Vector3 pos{
						position.x + (x * spacing - halfExtent),
						position.y + (y * spacing - halfExtent),
						position.z + (z * spacing - halfExtent)
					};

					// Fire each cube shot
					RpcFireShot_O(__this, pos, rotation, velocity, damage, someFlag, extra);
				}
			}
		}
		return; // Done with cube shots
	}

	// Normal single shot
	return RpcFireShot_O(__this, position, rotation, velocity, damage, someFlag, extra);
}

struct Vector3f {
	float x;
	float y;
	float z;
};

struct Quaternion4f {
	float x;
	float y;
	float z;
	float w;
};





void* lastspawned = nullptr;
void* (*old_PhotonInstantiate)(Unity::System_String*, Vector3f, Quaternion4f, float);
void* PhotonInstantiate(Unity::System_String* prefab, Vector3f pos, Quaternion4f rot, float scale) {
	lastspawned = old_PhotonInstantiate(prefab, pos, rot, scale);
	return lastspawned;
}


void* localplayer = nullptr;

typedef void* (*get_LocalPlayer_t)();
get_LocalPlayer_t get_LocalPlayer_original = nullptr;

void* get_LocalPlayer_hook() {
	localplayer = get_LocalPlayer_original(); // cache localplayer here
	return localplayer;
}

typedef DWORD* (__fastcall* get_righthand_t)(DWORD* __this);
get_righthand_t get_righthand_o = nullptr;

DWORD* __fastcall get_righthand(DWORD* __this) {
	DWORD* hand = get_righthand_o(__this);

	// Cast localplayer (void*) into DWORD*
	DWORD* localhand = nullptr;
	if (localplayer) {
		localhand = get_righthand_o(reinterpret_cast<DWORD*>(localplayer));
		printf("[LocalHand] Address: %p\n", localhand);
	}
	else {
		printf("[LocalHand] localplayer is null!\n");
	}

	return hand;
}

typedef bool(__fastcall* TryPickupTool_t)(
	void* __this,          // instance (the hidden "this" pointer)
	void* Tool,            // Tool JDFLDHBOOMM (class pointer)
	bool JBPMEHPADLG,
	bool GMKDBDKGEAH,
	bool JJDLLOGGKME,
	bool KEMJKPDKFGH
	);

TryPickupTool_t TryPickupTool_o = nullptr; // pointer to original function

// Our hook
bool __fastcall TryPickupTool_hook(
	void* __this,
	void* Tool,
	bool JBPMEHPADLG,
	bool GMKDBDKGEAH,
	bool JJDLLOGGKME,
	bool KEMJKPDKFGH
) {
	printf("[TryPickupTool] this=%p, Tool=%p, Flags={%d,%d,%d,%d}\n",
		__this,
		Tool,
		JBPMEHPADLG,
		GMKDBDKGEAH,
		JJDLLOGGKME,
		KEMJKPDKFGH
	);

	// Call the original
	return TryPickupTool_o(__this, Tool, JBPMEHPADLG, GMKDBDKGEAH, JJDLLOGGKME, KEMJKPDKFGH);
}



Vector3 cached_head_position; // persistent cache
typedef Vector3(*get_CurrentHeadPosition_t)(void*);
get_CurrentHeadPosition_t get_CurrentHeadPosition_original = nullptr;
Vector3 get_CurrentHeadPosition_hook(void* instance) {
	cached_head_position = get_CurrentHeadPosition_original(instance); // update cache

	return cached_head_position;
}

void spawnprefab()
{
	Vector3f prefabpos = { cached_head_position.x, cached_head_position.y, cached_head_position.z };
	Quaternion4f prefabrot = { 0, 0, 0, 0 };
	float scale = 1.f;

	if (globals::network::custompos)
	{
		prefabpos = {
			globals::network::prefabpos.x,
			globals::network::prefabpos.y,
			globals::network::prefabpos.z
		};
	}

	if (globals::network::customrot)
	{
		prefabrot = {
			globals::network::prefabrot.x,
			globals::network::prefabrot.y,
			globals::network::prefabrot.z,
			globals::network::prefabrot.w
		};
	}

	if (globals::network::customscale)
	{
		scale = globals::network::prefabscale;
	}

	for (int i = 0; i < globals::network::prefabamount; ++i)
	{
		Unity::System_String* prefab = Unity::CreateString(globals::network::selectedPrefabName.c_str());
		old_PhotonInstantiate(prefab, prefabpos, prefabrot, scale);
	}

	globals::network::spawnasset = false;
}



void forceequip()
{
	auto prefabscale = 1.f;
	Vector3f prepos = { 0, -100, 0 };
	Quaternion4f prerot = { 0, 0, 0 };
	Unity::System_String* prefabname = Unity::CreateString(globals::network::selectedPrefabName.c_str());
	
	auto prefab = old_PhotonInstantiate(prefabname, prepos, prerot, prefabscale); 
}

// Globals to cache the last call
void* g_cached_this = nullptr;
void* g_cached_object = nullptr;
void* g_cached_unknown = nullptr;


void* (*addmaxwalkspeed_o)(void*, float, void*, void*);

void* maxwalkspeed(void* __this, float speed, void* object, void* unknown) {
	// Cache the pointers
	g_cached_this = __this;
	g_cached_object = object;
	g_cached_unknown = unknown;
	float changedspeed = speed;



	if (globals::player::speedtoggle)
	{
		changedspeed = globals::player::speed;
	}

	return addmaxwalkspeed_o(__this, changedspeed, object, unknown);
}

void* (*get_networkedview_o)(void*);
void* get_networkedview(void* player) {
	return get_networkedview_o(player);
}

void* (*DestroyImmediate_o)(void*);
void* DestroyImmediate(void* object) {
	printf("destroy");
	return DestroyImmediate_o(object);
}

void* (*cv2setposition_o)(void*, Vector3);
void* cv2setposition(void* player, Vector3 position) {
	return cv2setposition_o(player, position);
}


struct PlayerInfo {
	void* playernameaddress;
	int playerid;
	void* playeraddress;
	void* photonplayer;
	void* networkedview;
};


static std::unordered_map<std::string, PlayerInfo> playerCache;
typedef int(__stdcall* get_PlayerId_t)(void* instance);
get_PlayerId_t get_PlayerId_o = nullptr;
Unity::System_String* (*old_get_PlayerName)(void*);
int __stdcall get_PlayerId_h(void* instance) {
	int id = get_PlayerId_o(instance);
	return id;
}

// Typedef for the original function
typedef void* (__stdcall* GetFromAccountId_t)(int accountId, bool flag);
GetFromAccountId_t getplayerfromid_o = nullptr;

// Our hook
void* __stdcall getplayerfromid_h(int accountId, bool flag) {
	// Call original function
	void* player = getplayerfromid_o(accountId, flag);



	return player; // Keep original behavior
}

// Typedef for the original function
typedef void* (__thiscall* get_photonplayer_t)(void* instance);
get_photonplayer_t get_photonplayer_o = nullptr;

// Our hook
void* __fastcall get_photonplayer_h(void* instance) {
	// Call original
	void* netPlayer = get_photonplayer_o(instance);



	return netPlayer; // Keep original behavior
}


typedef void* (*get_current_t)();
get_current_t get_current_o = nullptr;

// Hook function
void* get_current_h() {
	void* camera = get_current_o(); // Call original



	// Optional: modify camera pointer here if needed
	return camera;
}

typedef Vector3(*worldtoscreen_t)(void*, Vector3f, int);
worldtoscreen_t worldtoscreen_o = nullptr;

Vector3 worldtoscreen_h(void* camera, Vector3f position, int eye) {
	return worldtoscreen_o(camera, position, eye);
}

Unity::System_String* get_PlayerName(void* instance) {
	Unity::System_String* str = old_get_PlayerName(instance);
	int playerid = get_PlayerId_o(instance);

	void* playeraddress = nullptr;
	if (playerid != 0) {
		playeraddress = getplayerfromid_o(playerid, false);
	}

	void* photonplayer = nullptr;
	if (playeraddress) {
		photonplayer = get_photonplayer_o(playeraddress);
	}


	void* networkedview = nullptr;
	if (playeraddress) {
		networkedview = get_networkedview_o(playeraddress);
	}

	// --- Try fetching head position + screen pos ---
	Vector3 headPos = { 0, 0, 0 };
	Vector3 screenPos = { 0, 0, 0 };
	if (playeraddress && get_CurrentHeadPosition_original) {
		headPos = get_CurrentHeadPosition_original(playeraddress);

		void* cam = nullptr;
		if (get_current_o) {
			cam = get_current_o();
		}

		if (cam && worldtoscreen_o) {
			screenPos = worldtoscreen_o(cam, { headPos.x, headPos.y, headPos.z }, 2);
		}
	}

	if (str) {
		std::string name = str->ToString();
		globals::network::PlayerData* existingPlayer = globals::network::FindPlayerByName(name);

		if (!existingPlayer) {
			// New player - add to vector list
			globals::network::playerList.push_back({ name, playerid, playeraddress, photonplayer, networkedview });

			printf("[NEW] Player added to list: %s | Account ID: %d | Player Address: %p | Photon Player Address: %p | Networked View: %p "
				"| Position: %.2f, %.2f, %.2f | Screen: %.2f, %.2f, %.2f | Total players in list: %zu\n",
				name.c_str(), playerid, playeraddress, photonplayer, networkedview,
				headPos.x, headPos.y, headPos.z, screenPos.x, screenPos.y, screenPos.z, globals::network::playerList.size());
		}
		else {
			if (existingPlayer->playerId != playerid ||
				existingPlayer->playerAddress != playeraddress ||
				existingPlayer->photonPlayerAddress != photonplayer ||
				existingPlayer->networkedViewAddress != networkedview) {

				existingPlayer->playerId = playerid;
				existingPlayer->playerAddress = playeraddress;
				existingPlayer->photonPlayerAddress = photonplayer;
				existingPlayer->networkedViewAddress = networkedview;

				printf("[UPDATE] Player updated in list: %s | Account ID: %d | Player Address: %p | Photon Player Address: %p | Networked View: %p "
					"| Position: %.2f, %.2f, %.2f | Screen: %.2f, %.2f, %.2f\n",
					name.c_str(), playerid, playeraddress, photonplayer, networkedview,
					headPos.x, headPos.y, headPos.z, screenPos.x, screenPos.y, screenPos.z);
			}
		}
	}
	else {
		printf("Player Name: <null> | Player Name Address: %p | ActorID Instance: %p | Player Address: %p | Photon Player Address: %p | Networked View: %p "
			"| Position: %.2f, %.2f, %.2f | Screen: %.2f, %.2f, %.2f\n",
			instance, instance, playeraddress, photonplayer, networkedview,
			headPos.x, headPos.y, headPos.z, screenPos.x, screenPos.y, screenPos.z);
	}

	return str;
}


#include <iomanip> // for printing floats with precision

void* (*rpcauthoritycv2respawn_o)(void*, Vector3, Quaternion4f, bool, bool);

void* rpcauthoritycv2respawn(void* networkview, Vector3 position, Quaternion4f rotation, bool uk, bool uk2) {
	// Print the networkview pointer
	std::cout << "[RPC] networkview: " << networkview << std::endl;

	// Print position
	std::cout << "[RPC] Position: x=" << std::fixed << std::setprecision(3) << position.x
		<< ", y=" << position.y << ", z=" << position.z << std::endl;

	// Print rotation quaternion
	std::cout << "[RPC] Rotation: x=" << rotation.x
		<< ", y=" << rotation.y
		<< ", z=" << rotation.z
		<< ", w=" << rotation.w << std::endl;

	// Print boolean flags
	std::cout << "[RPC] uk: " << uk << ", uk2: " << uk2 << std::endl;

	// Call original function
	void* ret = rpcauthoritycv2respawn_o(networkview, position, rotation, uk, uk2);

	// Print return pointer
	std::cout << "[RPC] Return: " << ret << std::endl;

	return ret;
}


struct Rect
{
	float x;      // X position (top-left)
	float y;      // Y position (top-left)
	float width;  // Width of the rectangle
	float height; // Height of the rectangle

	Rect() : x(0), y(0), width(0), height(0) {}
	Rect(float _x, float _y, float _w, float _h)
		: x(_x), y(_y), width(_w), height(_h) {
	}
};



void* (*releasetoolsfrombothhands_O)(void*);
void* releasetoolsfrombothhands(void* player)
{

	return releasetoolsfrombothhands_O(player);
}

void* (*releasetoolsfromunequip_o)(void*);
void* releasetoolsfromunequip(void* player)
{

	return releasetoolsfromunequip_o(player);
}

void* (*get_networkedplayer_o)(void*);
void* get_networkedplayer(void* player)
{

	return get_networkedplayer_o(player);
}

void* (*get_playerprogression_o)(void*);
void* get_playerprogression(void* player)
{

	return get_playerprogression_o(player);
}

void* (*rezspawneffects_o)( void*, Vector3, Quaternion, Vector3, Quaternion);
void* rezspawneffects( void* object, Vector3 pos1, Quaternion rot1, Vector3 pos2, Quaternion rot2)
{

	return rezspawneffects_o(object, pos1, rot1, pos2, rot2);
}


typedef void* (*t_UnsafeCreateInstance)(void* elementType, void* length);
t_UnsafeCreateInstance o_UnsafeCreateInstance = nullptr;

// Hook function
void* hk_UnsafeCreateInstance(void* elementType, void* length)
{

	// Optional: inspect elementType or lengths here

	// Call the original function
	void* result = o_UnsafeCreateInstance(elementType, length);

	// Optional: inspect result, modify array, etc.
	return result;
}

typedef void* (*tGetType)(Unity::System_String* typeName);
tGetType oGetType = nullptr; // initialize this with the RVA from your dump

// Hookable wrapper / helper
void* GetType(Unity::System_String* typeName)
{
	if (!oGetType)
		return nullptr;


	return oGetType(typeName);
}

typedef void(__fastcall* tSetValue)(void* _this, void* value, int index);

// Pointers
tSetValue oSetValue = nullptr;

// Our hook
void __fastcall hkSetValue(void* _this, void* value, int index)
{

	oSetValue(_this, value, index);
}

void* (*RPC_o)(Unity::System_String*, void*, globals::network::Il2CppArray*);
void* RPC(Unity::System_String* methodName, void*	networkedPlayer, globals::network::Il2CppArray* paramters)
{

	return RPC_o(methodName, networkedPlayer, paramters);
}


bool (*cv2setseatedplayerer_o)(void* __this, void*);

bool cv2setseatedplayer(void* __this, void* player)
{
	// Get base of GameAssembly.dll
	static uintptr_t gameAssemblyBase = (uintptr_t)GetModuleHandleA("GameAssembly.dll");

	uintptr_t absAddr = (uintptr_t)player;
	uintptr_t rva = absAddr - gameAssemblyBase;

	printf("[CV2SetSeatedPlayer] nijerian RVA: 0x%llX | abs: %p | player: %p\n",
		(unsigned long long)rva, (void*)absAddr, player);

	return cv2setseatedplayerer_o(__this, player);
}


void* (*get_allcircuts)(void*);
void* get_circuts(void* cv2manager)
{
	printf("goet");
	return get_allcircuts(cv2manager);
}

void RamCrash(void* targetPlayer) {
	if (!targetPlayer)
		return;

	// Get the networked player & progression
	void* networkedPlayer = get_networkedplayer_o(targetPlayer);
	void* playerProgression = get_playerprogression_o(targetPlayer);
	if (!networkedPlayer || !playerProgression)
		return;

	// Get the networked view from progression
	void* networkedView = get_networkedview_o(playerProgression);
	if (!networkedView)
		return;

	// Prepare the "cheer" value
	int cheer = 1;

	// Get types
	Unity::System_String* intTypeName = Unity::CreateString("System.Int32");
	void* intType = GetType(intTypeName);

	Unity::System_String* objectArrayName = Unity::CreateString("System.Object[]");
	void* objectArrayType = GetType(objectArrayName);
	printf("\n[INFO] Int32 Type Name Ptr: %p | Int32 Type Ptr: %p\n", intTypeName, intType);
	printf("\n[INFO] Object[] Type Name Ptr: %p | Object[] Type Ptr: %p\n", objectArrayName, objectArrayType);

	// Create array
	void* parameters = o_UnsafeCreateInstance(objectArrayType, (void*)1);
	
	// Box the int
	//void* boxedCheer = o_UnsafeCreateInstance(intType, &cheer);

	// Set the array element
	//oSetValue(parameters, boxedCheer, 0);


	Unity::System_String* rpcname = Unity::CreateString("RpcPlayLevelUpFeedback");
	for (int i = 0; i < 3; ++i) {
		printf("test");
	}
}



void (*old_OnUpdate)(void* instance);
void OnUpdate(void* instance) {
	if (instance) {
		for (auto it = globals::network::playerList.begin(); it != globals::network::playerList.end(); ) {
			Vector3 pos = { 0,0,0 };
			if (it->playerAddress && get_CurrentHeadPosition_original) {
				pos = get_CurrentHeadPosition_original(it->playerAddress);
			}

			if (pos.x == 0.f && pos.y == 0.f && pos.z == 0.f) {
				printf("[REMOVE] Player %s | ID: %d removed (position = 0,0,0)\n",
					it->name.c_str(), it->playerId);
				it = globals::network::playerList.erase(it);
			}
			else {
				++it;
			}
		}

		if (globals::network::ramcrash)
		{
			void* player = globals::network::FindPlayerById(globals::network::targetPlayerId);
			RamCrash(player);
			globals::network::ramcrash = false;
		}

		if (globals::network::bring)
		{
			void* player = globals::network::FindPlayerById(globals::network::targetPlayerId);
			void* blocalplayer = get_LocalPlayer_original();
			Vector3 localheadpositon = get_CurrentHeadPosition_original(blocalplayer);
			cv2setposition_o(player, localheadpositon);
			globals::network::bring = false;
		}

		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && globals::combat::holdtofire && cached_this) {
			Fire_O(cached_this, 1.f, cached_parkbank);
		}

		if (globals::ui::assetspawn && (GetAsyncKeyState('R') & 0x8000)) {
			globals::network::spawnasset = true;

		}

		if (globals::network::witchorbit)
		{
			void* player = globals::network::FindPlayerById(globals::network::targetPlayerId);
			Vector3 prepos = get_CurrentHeadPosition_original(player);
			Vector3f center = { prepos.x, prepos.y, prepos.z };

			const int prefabCount = 20;       // number of prefabs in orbit
			const float radius = 2.0f;        // distance from player, adjust to make gap not too big
			const float prefabScale = 1.f;
			Quaternion4f rotation = { 0, 0, 0, 0 };
			Unity::System_String* prefabName = Unity::CreateString("[Quest_VolleyEnemy_Projectile]");

			for (int i = 0; i < prefabCount; i++)
			{
				float angle = (2.0f * 3.14159265f / prefabCount) * i;  // angle in radians
				Vector3f pos;
				pos.x = center.x + radius * cos(angle);
				pos.y = center.y;  // keep at player height, adjust if you want orbit up/down
				pos.z = center.z + radius * sin(angle);

				old_PhotonInstantiate(prefabName, pos, rotation, prefabScale);
			}

			globals::network::witchorbit = false;
		}


		if (globals::network::disarm) {
			void* player = globals::network::FindPlayerById(globals::network::targetPlayerId);
			releasetoolsfromunequip_o(player);
			releasetoolsfrombothhands_O(player);
			globals::network::disarm = false;
		}

		if (globals::network::disarmall) {
			for (auto& player : globals::network::playerList) {
				if (player.playerAddress) {
					releasetoolsfrombothhands_O(player.playerAddress);
					releasetoolsfromunequip_o(player.playerAddress);
					printf("[DisarmAll] Disarmed player: %s | ID: %d | Addr: %p\n",
						player.name.c_str(), player.playerId, player.playerAddress);
				}
			}
			globals::network::disarmall = false;
		}

		if (globals::network::teleportToPlayer) {
			void* player = globals::network::FindPlayerById(globals::network::targetPlayerId);
			void* local = get_LocalPlayer_original();
			Vector3 position = get_CurrentHeadPosition_original(player);
			Quaternion4f rotation = { 1, 1, 1, 1 };
			cv2setposition_o(local, position);
			globals::network::teleportToPlayer = false;
		}

		if (globals::network::spawnasset) {
			spawnprefab();
		}

		if (globals::player::changespeed && g_cached_this) {
			addmaxwalkspeed_o(g_cached_this, globals::player::speed, g_cached_object, g_cached_unknown);
		}

		return old_OnUpdate(instance);
	}
}








void (*SpawnConsumableForLocalPlayer_O)(
	DWORD* __this,
	Unity::System_String* prefabName,
	unsigned long* longPrt,
	globals::Vector3f Vec,
	globals::Quaternion4f quat,
	float scale,
	INT32* BFDCKEJIDML,
	DWORD* method
	);


void SpawnConsumableForLocalPlayer_H(	DWORD* __this,	Unity::System_String* prefabName,	unsigned long* longPrt,	globals::Vector3f Vec,	globals::Quaternion4f quat,	float scale,	INT32* BFDCKEJIDML,	DWORD* method) {

	if (!globals::network::foodsploit) {
		SpawnConsumableForLocalPlayer_O(__this, prefabName, longPrt, Vec, quat, scale, BFDCKEJIDML, method);
		return;
	}


	Unity::System_String* foodGuidToUse = prefabName;
	int foodCountToUse = 1;
	globals::Vector3f posToUse = Vec;
	globals::Quaternion4f rotToUse = quat;
	float scaleToUse = scale;

	if (globals::network::customfood && globals::network::foodsploit) {
		foodGuidToUse = Unity::CreateString(globals::network::foodGuid);
	}


	if (globals::network::customfoodamount && globals::network::foodsploit) {
		foodCountToUse = globals::network::foodcount;
	}


	if (globals::network::customfoodsize && globals::network::foodsploit) {
		scaleToUse = globals::network::foodsize;
	}


	if (globals::network::customfoodposition && globals::network::foodsploit) {
		posToUse = globals::network::foodposition;
	}


	if (globals::network::customfoodrotation) {
		rotToUse = globals::network::foodrotation;
	}



	for (int i = 0; i < foodCountToUse; ++i) {
		globals::Quaternion4f currentRot = rotToUse;

		if (globals::network::randomrotation) {
			static std::random_device rd;
			static std::mt19937 gen(rd());
			std::uniform_real_distribution<float> dist(-360.0f, 360.0f);

			currentRot.x = dist(gen);
			currentRot.y = dist(gen);
			currentRot.z = dist(gen);
		}


		SpawnConsumableForLocalPlayer_O(
			__this,
			foodGuidToUse,
			longPrt,
			posToUse,
			currentRot,
			scaleToUse,
			BFDCKEJIDML,
			method
		);
	}

}




typedef void* (*TryUpdatePlayerListTask_t)(void* __this, Unity::System_String* playerListString);
TryUpdatePlayerListTask_t TryUpdatePlayerListTask_original = nullptr;

void* TryUpdatePlayerListTask_hook(void* __this, Unity::System_String* playerListString) {
	if (playerListString) {
		std::string listStr = playerListString->ToString(); // <-- your helper

	}
	else {

	}

	// Call original function to maintain normal behavior
	return TryUpdatePlayerListTask_original(__this, playerListString);
}


void (*old_nophook)();
void nophook() {

	return;
}





