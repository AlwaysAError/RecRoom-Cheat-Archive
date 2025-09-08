#pragma once
#include "MinHook.h"
#include <cmath>
#include <Windows.h>
#include <vector>
#include "functions.h"


uintptr_t GA = (uintptr_t)GetModuleHandleA("GameAssembly.dll");
uintptr_t RF = (uintptr_t)GetModuleHandleA("Referee.dll");





void Hooks()
{
	printf("GA: 0x%llx | RF: 0x%llx\n", GA, RF);
	MH_Initialize();




	MH_CreateHook(reinterpret_cast<void*>(reinterpret_cast<uint64_t>(GetModuleHandleA("Referee.dll")) + 0x760C90), &nophook, reinterpret_cast<void**>(&old_nophook));
	MH_EnableHook(reinterpret_cast<void*>(reinterpret_cast<uint64_t>(GetModuleHandleA("Referee.dll")) + 0x760C90));

	MH_CreateHook(reinterpret_cast<void*>(reinterpret_cast<uint64_t>(GetModuleHandleA("Referee.dll")) + 0x76F870), &nophook, reinterpret_cast<void**>(&old_nophook));
	MH_EnableHook(reinterpret_cast<void*>(reinterpret_cast<uint64_t>(GetModuleHandleA("Referee.dll")) + 0x76F870));

	/*                                         Rec Room Functions                                         */
	MH_CreateHook(reinterpret_cast<void**>(GA + (0x19F53F0)), &get_isFlyingEnabled_h, (void**)&get_IsFlyingEnabled_o);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x19F53F0)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0x19E1C90)), &AddFlyEnabled_h, (void**)&AddFlyEnabled_o);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x19E1C90)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0x1553020)), &get_IsItemUnlockedLocally_h, (void**)&get_IsItemUnlockedLocally_o);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x1553020)));



	MH_CreateHook(reinterpret_cast<void**>(GA + (0x2231540)), &Get_IsDeveloper_h, (void**)&Get_IsDeveloper_o);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x2231540)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0x1F5C990)), &get_IsOnCooldown_H, (void**)&get_IsOnCooldown_O);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x1F5C990)));



	MH_CreateHook(reinterpret_cast<void**>(GA + (0x1F5F730)), &Set_Ammunition_H, (void**)&Set_Ammunition_O);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x1F5F730)));



	MH_CreateHook(reinterpret_cast<void**>(GA + (0x1552C20)), &IsAvatarItemAlreadyPurchased_H, (void**)&IsAvatarItemAlreadyPurchased_O);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x1552C20)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0x1552DB0)), &IsAvatarItemUnlocked_H, (void**)&IsAvatarItemUnlocked_O);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x1552DB0)));
	/*                                         Rec Room Functions                                         */



	/*                                              Movement                                              */

	/*                                              Movement                                              */



	/*                                            Unity Engine                                            */

	// Replace your current FOV hook with:
	MH_CreateHook(reinterpret_cast<void**>(GA + (0x9C095B0)), &FOV_H, (void**)&FOV_O);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x9C095B0)));






	/*                                            Quest Related                                            */


	MH_CreateHook(reinterpret_cast<void**>(GA + (0x1F5C4E0)), &get_CurrentRecoilMultiplier_H, (void**)&get_CurrentRecoilMultiplier_O);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x1F5C4E0)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0x1F5C3B0)), &get_CurrentProjectileSpeed_H, (void**)&get_CurrentProjectileSpeed_O);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x1F5C3B0)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0x1F530A0)), &Fire_H, (void**)&Fire_O);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x1F530A0)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0xE736C0)), &get_CanUseClothingCustomizer_h, (void**)&get_CanUseClothingCustomizer_o);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0xE736C0)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0xE6D520)), &get_CanUseShareCamera_h, (void**)&get_CanUseShareCamera_o);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0xE6D520)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0xFD5590)), &get_CanUseStreamingCam_h, (void**)&get_CanUseStreamingCam_o);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0xFD5590)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0x9C64AC0)), &set_eulerAngles_H, (void**)&set_eulerAngles_O);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x9C64AC0)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0x2139E00)), &CV2UnequipSlots_H, (void**)&CV2UnequipSlots_O);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x2139E00)));



	MH_CreateHook(reinterpret_cast<void**>(GA + (0x2135F00)), &CV2GoToRoom_H, (void**)&CV2GoToRoom_O);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x2135F00)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0x2138C70)), &CV2ShowBannerNotification_H, (void**)&CV2ShowBannerNotification_O);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x2138C70)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0x1F58A70)), &RpcFireShot_H, (void**)&RpcFireShot_O);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x1F58A70)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0x7A6E490)), &nophook, (void**)&old_nophook);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x7A6E490)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0x21C5340)), &RpcPlayLevelUpFeedback_H, (void**)&RpcPlayLevelUpFeedback_O);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x21C5340)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0xFB2CB0)), &DoesLocalPlayerOwnKeyG, (void**)&old_DoesLocalPlayerOwnKeyG);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0xFB2CB0)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0xFB2E20)), &DoesLocalPlayerOwnKeyL, (void**)&old_DoesLocalPlayerOwnKeyL);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0xFB2E20)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0x21C5340)), &RpcPlayLevelUpFeedback_H, (void**)&RpcPlayLevelUpFeedback_O);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x21C5340)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0xF46F80)), &OnUpdate, (void**)&old_OnUpdate);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0xF46F80)));


	MH_CreateHook(reinterpret_cast<void**>(GA + (0x228C9C0)), &PhotonInstantiate, (void**)&old_PhotonInstantiate);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x228C9C0)));

	

	MH_CreateHook(reinterpret_cast<void**>(GA + (0xFF9FA0)), &SpawnConsumableForLocalPlayer_H, (void**)&SpawnConsumableForLocalPlayer_O);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0xFF9FA0)));


	MH_CreateHook(reinterpret_cast<void**>(GA + (0x14469D0)), &TryUpdatePlayerListTask_hook, (void**)&TryUpdatePlayerListTask_original);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x14469D0)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0x215F5A0)), &get_LocalPlayer_hook, (void**)&get_LocalPlayer_original);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x215F5A0)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0x215DF10)), &get_CurrentHeadPosition_hook, (void**)&get_CurrentHeadPosition_original);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x215DF10)));

//	MH_CreateHook(reinterpret_cast<void**>(GA + (0xC17060)), &get_righthand, (void**)&get_righthand_o);
//	MH_EnableHook(reinterpret_cast<void**>(GA + (0xC17060)));

//	MH_CreateHook(reinterpret_cast<void**>(GA + (0x21A2220)), &TryPickupTool_hook, (void**)&TryPickupTool_o);
//	MH_EnableHook(reinterpret_cast<void**>(GA + (0x21A2220)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0x19E2180)), &maxwalkspeed, (void**)&addmaxwalkspeed_o);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x19E2180)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0x215FD20)), &get_PlayerName, (void**)&old_get_PlayerName);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x215FD20)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0x215FBD0)), &get_PlayerId_h, (void**)&get_PlayerId_o);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x215FBD0)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0x2140E50)), &getplayerfromid_h, (void**)&getplayerfromid_o);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x2140E50)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0x215F970)), &get_photonplayer_h, (void**)&get_photonplayer_o);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x215F970)));	

	MH_CreateHook(reinterpret_cast<void**>(GA + (0x9C08140)), &get_current_h, (void**)&get_current_o);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x9C08140)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0x9C079C0)), &worldtoscreen_h, (void**)&worldtoscreen_o);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x9C079C0)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0x2158530)), &rpcauthoritycv2respawn, (void**)&rpcauthoritycv2respawn_o);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x2158530)));



	MH_CreateHook(reinterpret_cast<void**>(GA + (0x85446C0)), &get_networkedview, (void**)&get_networkedview_o);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x85446C0)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0x21576D0)), &releasetoolsfrombothhands, (void**)&releasetoolsfrombothhands_O);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x21576D0)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0x21576A0)), &releasetoolsfromunequip, (void**)&releasetoolsfromunequip_o);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x21576A0)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0x18A5E30)), &cv2setseatedplayer, (void**)&cv2setseatedplayerer_o);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x18A5E30)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0x215F7E0)), &get_networkedplayer, (void**)&get_networkedplayer_o);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x215F7E0)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0xB701B0)), &get_playerprogression, (void**)&get_playerprogression_o);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0xB701B0)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0x7520DD0)), &hk_UnsafeCreateInstance, (void**)&o_UnsafeCreateInstance);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x7520DD0)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0x7522430)), &hkSetValue, (void**)&oSetValue);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x7522430)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0x75358E0)), &GetType, (void**)&oGetType);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x75358E0)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0x11028E0)), &get_circuts, (void**)&get_allcircuts);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x11028E0)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0x8547210)), &RPC, (void**)&RPC_o);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x8547210)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0x9C54770)), &DestroyImmediate, (void**)&DestroyImmediate_o);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x9C54770)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0x1BA6DA0)), &rezspawneffects, (void**)&rezspawneffects_o);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x1BA6DA0)));

	MH_CreateHook(reinterpret_cast<void**>(GA + (0x2158850)), &cv2setposition, (void**)&cv2setposition_o);
	MH_EnableHook(reinterpret_cast<void**>(GA + (0x2158850)));

	//MH_CreateHook(reinterpret_cast<void**>(GA + (0x11003D0)), &sendmajornotification, (void**)&sendmajornotification);
	//MH_EnableHook(reinterpret_cast<void**>(GA + (0x11003D0)));













}
