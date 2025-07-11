#pragma once

enum class RoleId // first param (aka roleid) // i think this is just for GameRoles, RoomRoles seem to have seperate ids
{
	AG_EVERYONE = 0,
	GAME_ROLE_1 = 2,
	GAME_ROLE_2 = 4,
	GAME_ROLE_3 = 8,
	GAME_ROLE_4 = 16,
	GAME_ROLE_5 = 32,
	GAME_ROLE_6 = 64,
	GAME_ROLE_7 = 128,
	GAME_ROLE_8 = 256,
	GAME_ROLE_9 = 512,
	GAME_ROLE_10 = 1024,
	GAME_ROLE_11 = 2048,
	GAME_ROLE_12 = 4096,
	GAME_ROLE_13 = 8192,
	GAME_ROLE_14 = 16384,
	GAME_ROLE_15 = 32768,
	GAME_ROLE_16 = 65536,
	GAME_ROLE_17 = 131072,
	GAME_ROLE_18 = 262144,
	GAME_ROLE_19 = 524288,
	GAME_ROLE_20 = 1048576,
	AG_IN_GAME = 2097152,
	AG_ELIMINATED = 4194304,
	AG_ROLE_3 = 8388608,
	AG_ROLE_4 = 16777216,
	AG_ROLE_5 = 33554432,
	AG_ROLE_6 = 67108864,
	AG_ROLE_7 = 134217728,
	AG_ROLE_8 = 268435456,
	AG_ROLE_9 = 536870912,
	AG_ROLE_10 = 1073741824,
	AG_ROLE_11 = -2147483648,
};

enum class RoomRolePermission // role_perm FOR ROOM ROLES NOT GAME ROLES
{
	INVALID = -1,
	CAN_EDIT_ROOM_ROLES = 1,
	VOTE_KICK_PERMISSION = 3,
	CAN_INVITE = 4,
	CAN_TALK = 6,
	CAN_PRINT_PHOTOS = 7,
	CAN_START_GAMES = 8,
	CAN_SELF_REVIVE = 9,
	AUTO_ASSIGNED_GAME_ROLES = 11,
	CAN_CHANGE_GAME_MODE = 12,
	CAN_USE_MAKER_PEN = 13,
	CAN_USE_DELETE_ALL_BUTTON = 14,
	CAN_SAVE_INVENTIONS = 15,
	DISABLE_MIC_AUTO_MUTE = 16,
	CAN_END_GAMES_EARLY = 17,
	CAN_USE_SHARE_CAM = 18,
	DEPRECATED_CAN_EDIT_CIRCUITS = 19,
	CAN_SPAWN_INVENTIONS = 20,
	CAN_SPAWN_CONSUMABLES = 21,
	CAN_USE_ROOM_RESET_BUTTON = 22,
	CAN_USE_PLAY_GIZMOS_TOGGLE = 23,
	AUTO_ASSIGNED_PLAYER_TAGS = 24,
	CAN_USE_RRS = 25,
	ROOM_LEVEL_THRESHOLD = 1000,
	CAN_SAVE_ROOM = 1001,
	CAN_PUBLISH_ROOM = 1002,
	CAN_CLONE_ROOM = 1003,
	CAN_RESTORE_ROOM = 1004,
	CAN_EDIT_MAIN_ROOM_SETTINGS = 1006,
	CAN_EDIT_ROOM_ECON_SETTINGS = 1007,
	CAN_CREATE_SUBROOMS = 1008,
	CAN_NAME_SUBROOMS = 1009,
	CAN_CLONE_SUBROOMS = 1010,
	CAN_MOVE_SUBROOMS = 1011,
	CAN_DELETE_SUBROOMS = 1012,
	CAN_EDIT_SUBROOM_SETTINGS = 1013,
	CAN_RESET_CLOUD_VARIABLES = 1014,
	CAN_DELETE_CLOUD_VARIABLES = 1015,
	CAN_EDIT_ROOM_PROGRESSION = 1016,
	CAN_REMOVE_ROOM_BANS = 1017,
	CAN_ADD_ROOM_BANS = 1018,
};

enum class GameRolePermission
{
	INVALID = -1,
	TELEPORT_DELAY = 2,
	CAN_MOVE = 4,
	CAN_FLY = 8,
	IS_INVINCIBLE = 9,
	ITEM_PICKUP_RESTRICTIONS = 10,
	ITEM_PICKUP_ALLOWLIST = 11,
	ITEM_PICKUP_BLOCKLIST = 12,
	CAN_SWITCH_TEAMS = 13,
	MAX_TELEPORT_DISTANCE = 14,
	MAX_TELEPORT_DROP_HEIGHT = 15,
	VOICE_ROLLOFF_MAX_DISTANCE = 17,
	HIDES_NAME = 20,
	VR_WALK_SPEED = 21,
	VR_CAN_SPRINT = 22,
	SCREENS_WALK_SPEED = 24,
	SCREENS_CAN_SPRINT = 25,
	VR_CAN_JUMP = 28,
	VR_CAN_DODGE = 29,
	SCREENS_CAN_JUMP = 30,
	SCREENS_CAN_DODGE = 31,
	MAX_TELEPORT_ANGLE = 32,
	ENABLE_EQUIP_SLOT_HIP = 34,
	EQUIP_RESTRICTIONS_HIP = 35,
	EQUIP_HIP_ALLOWLIST = 36,
	EQUIP_HIP_BLOCKLIST = 37,
	EQUIP_RESTRICTIONS_SHOULDER = 39,
	EQUIP_SHOULDER_ALLOWLIST = 40,
	EQUIP_SHOULDER_BLOCKLIST = 41,
	SCREENS_DEFAULT_THIRD_PERSON_CONTROL_TYPE = 42,
	SCREENS_DEFAULT_FIRST_PERSON_CONTROL_TYPE = 43,
	VR_MAX_JUMP_HEIGHT = 44,
	SCREENS_MAX_JUMP_HEIGHT = 45,
	SCREENS_CAN_WALL_RUN = 48,
	VR_CAN_WALL_RUN = 49,
	VR_CAN_GET_PUSHED = 50,
	SCREENS_CAN_GET_PUSHED = 51,
	VR_CAN_RAM = 52,
	SCREENS_CAN_RAM = 53,
	VR_SPRINT_MAX_SPEED_WALK_SPEED_MULTIPLIER = 55,
	SCREENS_SPRINT_MAX_SPEED_WALK_SPEED_MULTIPLIER = 56,
	CAN_ALWAYS_SPRINT = 57,
	AIR_CONTROL_PARAMETER = 58,
	CAN_JUMP_CUTOFF = 59,
	CAN_CLAMBER = 60,
	WALL_RUN_DURATION = 61,
	WALL_RUN_DROP_RATE_PARAMETER = 62,
	WALL_RUN_START_SPEED_BOOST = 63,
	WALL_RUN_JUMP_HEIGHT = 64,
	WALL_RUN_JUMP_DIRECTION_PARAMETER = 65,
	WALL_RUN_JUMP_AIR_CONTROL_MULTIPLIER = 66,
	CAN_SLIDE = 67,
	CAN_SLIDE_DOWN_SLOPES = 68,
	SLIDE_MIN_DURATION = 69,
	SLIDE_STEERING_PARAMETER = 70,
	SLIDE_START_SPEED_BOOST = 71,
	SLIDE_AIR_CONTROL_MULTIPLIER = 72,
	CAN_WALL_CLIMB = 73,
	HIDES_AVATAR = 75,
	PLAYER_TAGS = 76,
	ADD_PLAYER_TAGS = 77,
	REMOVE_PLAYER_TAGS = 78,
	CAN_USE_MAKER_PEN = 80,
	CAN_SAVE_INVENTIONS = 81,
	CAN_SPAWN_INVENTIONS = 82,
	CAN_USE_ROOM_RESET_BUTTON = 83,
	CAN_USE_DELETE_ALL_BUTTON = 84,
	CREATION_RESTRICTIONS_APPLY = 85,
	CAN_CREATE_ROLE_ASSIGNMENT_CHIPS = 86,
	CAN_USE_PLAY_GIZMOS_TOGGLE = 87,
};

struct PlayerRoomRoleManager : MonoBehaviourPun {	

	typedef void (*StaticConstructor_t)(PlayerRoomRoleManager* hashtable);
	static PlayerRoomRoleManager* ctor()
	{
		Il2CppClass* klass = FindClass("RecRoom.Systems.PlayerRoles.PlayerRoomRoleManager");
		PlayerRoomRoleManager* object = (PlayerRoomRoleManager*)il2cpp_object_new_spoof(klass);
		if (object == nullptr)
			return nullptr;
		const auto func = (StaticConstructor_t)(methods::RecRoomSystemsPlayerRoles::PlayerRoomRoleManager::ctor);
		func(object);
		return object;
	}

};

struct PlayerGameRoleManager : MonoBehaviourPun {

	typedef PlayerGameRoleManager* (*get_Instance_t)();
	static PlayerGameRoleManager* get_Instance() {
		const auto func = (get_Instance_t)(methods::RecRoomSystemsPlayerRoles::PlayerGameRoleManager::get_Instance);
		return func();
	}

};

struct ExecParams : Component { // this changed since 2023, to what? fuck knows...

	typedef ExecParams* (*get_ExecParams_t)(ExecParams* instance);
	static ExecParams* get_ExecParams() { // maybe this is NewEmpty BUT WHY IS IT IN FUCKING PlayerRoomRoleManager CLASS WTF
		const auto func = (get_ExecParams_t)(GameAssembly + 0xDF7DD0); // PlayerRoomRoleManager first static function that returns a class
		return func(nullptr); // why the fuck does PlayerRoomRoleManager have this ???
	}

};