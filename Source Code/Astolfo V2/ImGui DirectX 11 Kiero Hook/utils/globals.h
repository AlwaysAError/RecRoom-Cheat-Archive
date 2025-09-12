#pragma once
#include <cstddef> // for std::size_t
#include <string>
#include <vector>
#include "..\utils\globals.h"

namespace globals
{
	namespace ui
	{
		inline bool mainui = false;
		inline bool playerlistwindow = false;
	}

    namespace player
    {
        inline bool spinbot = false;
        inline bool developer = false;
        inline bool fovtoggle = false;
        inline bool speedtoggle = false;
        inline bool changespeed = false;
        inline float fov = 60.0f;
        inline float speed = 3.5f;
    }

    namespace inventory
    {
        inline bool unlockkeys = false;
        inline bool sharecamera = false;
        inline bool steamercamera = false;
        inline bool clothingcustomizer = false;
        inline bool clothing = false;

    }

    namespace movement
    {
        inline bool dynamicfly = false;
        inline bool staticfly = false;
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

    struct Vector3 {
        float x;
        float y;
        float z;
    };

    struct ImVec2 {
        float x;
        float y;
    };

    namespace network
    {
        inline bool disableuneqipfromslots = false;
        inline bool disablegotoroom = false;
        inline bool disablebannercv2 = false;
        inline bool disableramcrashcheer = false;
        inline bool disableramcrashbullets = false;
		inline bool forceequipall = false;
        inline bool foodsploit = false;
        inline bool customfood = false;
        inline bool customfoodsize = false;
        inline bool customfoodposition = false;
		inline bool radioopen = false;
        inline bool customfoodrotation = false;
        inline bool customfoodamount = false;
		inline bool equipplayer = false;
		inline bool esp = false;
		inline bool objectspawn = false;
		inline bool changeheadscale = false;
        inline bool randomrotation = false;
		inline bool foodassetspawn = false;
		inline bool bringplr = false;
		inline bool bringall = false;
		inline bool voidall = false;
		inline bool test = false;

        inline float foodsize = 1.0f;
        inline int foodcount = 1;
        inline Vector3f foodposition = { 0, 0, 0 };
        inline Quaternion4f foodrotation = { 0, 0, 0, 0 };



        typedef struct Food
        {
            const char* frie;
            const char* guid;
            
        } Food;
        //  Food Liste (NEW)
        struct PlayerData {
            std::string name;
            int playerId;
			int playerindex;
			int playerping;
            void* playerAddress;
            void* photonPlayerAddress;
            void* networkedViewAddress;
            Vector3 position;      // World position
            Vector3 screenPosition; // Screen position
        };

		struct PlayerPositions {
			int playerid;
			Vector3 worldposition;
			Vector3 screenposition;
		};

		inline std::vector<PlayerPositions> playerPoses;
        inline std::vector<PlayerData> playerList;

        inline void ClearPlayers() {
            playerList.clear();
        }

        inline size_t GetPlayerCount() {
            return playerList.size();
        }

        inline PlayerData* FindPlayerByName(const std::string& name) {
            for (auto& player : playerList) {
                if (player.name == name) {
                    return &player;
                }
            }
            return nullptr;
        }

        inline void* FindPlayerById(int playerId) {
            for (auto& player : playerList) {
                if (player.playerId == playerId) {
                    return player.playerAddress;
                }
            }
            return nullptr;
        }

        inline std::string selectedPlayerName = "";
        inline int selectedPlayerId = -1;
		inline int localplayerid = -1;
		inline bool passedverification = false;
        inline bool teleportToPlayer = false;
        inline bool voidplayers = false;
        inline bool witchorbit = false;
        inline int targetPlayerId = -1;
        inline bool refreshPlayerList = false;
		inline bool headscaleon = false;
		inline float headscale = 1.0f;
        inline bool sendnotification = false;
        inline bool disarm = false;
        inline bool disarmall = false;
        inline bool ramcrash = false;
        inline bool bring = false;
        inline bool antispawnban = false;
        static ImVec2 PlayerListPos;
        static ImVec2 PlayerListSize;
        typedef struct Il2CppArray
        {
            void* klass;
            void* monitor;
            void* bounds;
            size_t max_length;
            void* vector[32];
        } Il2CppArray;


        inline const char* list[] = {
	"(FullBodyPuppetProp)",
	"[RootBeer_HackolaConsumableTool]",
	"[RootBeer_PixelPop_ConsumableTool]",
	"[CakePops_CandylandConsumableTool]",
	"[Popcorn_MonsterMunchies_ConsumableTool]",
	"[Microphone_Conference]",
	"[Sandbox_Mirror]",
	"[AudioEffectZone]",
	"[Consumables_Sparkler]",
	"[Consumables_Sparkler]",
	"[Consumables_Donut_BostonCreme]",
	"(HolotarProjector_CV1)",
	"(HolotarProjector_CV2)",
	"[ArenaManager]",
	"[Arena_AutomaticGun]",
	"[Arena_EMP]",
	"[Arena_Grenade]",
	"[Arena_Pistol]",
	"[Arena_PowerWeapon_BeamGun]",
	"[Arena_RailGun]",
	"[Arena_RocketLauncher]",
	"[Arena_Shotgun]",
	"[Arrow]",
	"[Basketball]",
	"[BattleRoyaleManager]",
	"[BowlingManager]",
	"[Bucket]",
	"[CharadesManager]",
	"[CharadesPen]",
	"[Charades_Stage]",
	"[Crossbow]",
	"[Crossbow_Hunter]",
	"[DiscGolfManager]",
	"[DodgeballManager]",
	"[ElectricalPole_Sandbox]",
	"[FlagAndGoal]",
	"[Giftbox]",
	"[Glider]",
	"[Grenade]",
	"[IBeam_10M_Sandbox]",
	"[Longbow]",
	"[LootChest]",
	"[LootChest_SciFi]",
	"[LootChest_Stuntrunner]",
	"[LootChest_Stuntrunner_Store_Smaller]",
	"[MakerPen]",
	"[MakerPen_Giftbox]",
	"[MicrophoneManager]",
	"[Microphone]",
	"[MiniLootChest_SciFi]",
	"[OrientationManager]",
	"[PaddleballBall]",
	"[PaddleballManager]",
	"[PaintballAssaultRifle]",
	"[PaintballGrenadeLauncher]",
	"[PaintballGun]",
	"[PaintballManager]",
	"[PaintballRifleScoped]",
	"[PaintballShield]",
	"[PaintballShotgun]",
	"[Paintball_PaintThrower]",
	"[PingpongBall]",
	"[PoolCue]",
	"[PoolTable]",
	"[ProximityMine]",
	"[QuestMeatSword]",
	"[QuestShield]",
	"[QuestSword]",
	"[Quest_Boulder]",
	"[Quest_Dracula1_1H-Crossbow]",
	"[Quest_Dracula1_BasicBoneMeleeEnemy]",
	"[Quest_Dracula1_BasicChargingWolfEnemy]",
	"[Quest_Dracula1_BasicLungingBatEnemy]",
	"[Quest_Dracula1_BasicRangedBatEnemy]",
	"[Quest_Dracula1_Bat_Plushy]",
	"[Quest_Dracula1_BlunderBuss]",
	"[Quest_Dracula1_BossBatDecoyEnemy]",
	"[Quest_Dracula1_ChestCoins_Large]",
	"[Quest_Dracula1_ChestCoins_Medium]",
	"[Quest_Dracula1_ChestCoins_Small]",
	"[Quest_Dracula1_CollectablePumpkin_Small]",
	"[Quest_Dracula1_Collectable_Large]",
	"[Quest_Dracula1_Collectable_Small]",
	"[Quest_Dracula1_Collectable_Wall]",
	"[Quest_Dracula1_Crossbow_Hunter]",
	"[Quest_Dracula1_DraculaBossBat]",
	"[Quest_Dracula1_DraculaBoss]",
	"[Quest_Dracula1_Flintlock]",
	"[Quest_Dracula1_Ground_Bone_ThrownEnemy]",
	"[Quest_Dracula1_Ground_MusketEnemy]",
	"[Quest_Dracula1_LootChest]",
	"[Quest_Dracula1_Manager]",
	"[Quest_Dracula1_MiniBossBoneMeleeEnemy]",
	"[Quest_Dracula1_MiniBossCoins_Bat]",
	"[Quest_Dracula1_MiniBossCoins_BoneMelee]",
	"[Quest_Dracula1_MiniBossCoins_BoneThrower]",
	"[Quest_Dracula1_MiniBossCoins_Musket]",
	"[Quest_Dracula1_MiniBossCoins_Wolf]",
	"[Quest_Dracula1_MiniBossGroundBoneThrownEnemy]",
	"[Quest_Dracula1_MiniBossGround_Musket]",
	"[Quest_Dracula1_MiniBossLungingWolfEnemy]",
	"[Quest_Dracula1_MiniBossRangedBatEnemy]",
	"[Quest_Dracula1_MiniBossSkeletonBone]",
	"[Quest_Dracula1_PitchFork]",
	"[Quest_Dracula1_Rake]",
	"[Quest_Dracula1_Rope]",
	"[Quest_Dracula1_Shovel]",
	"[Quest_Dracula1_SkeletonBone]",
	"[Quest_Dracula1_StoreLootChest]",
	"[Quest_Goblin1_Manager]",
	"[Quest_Goblin2_Manager]",
	"[Quest_Goblin_BasicFlyingRangedEnemy]",
	"[Quest_Goblin_BasicGroundMeleeEnemy]",
	"[Quest_Goblin_BasicGroundMeleeEnemy_Pike]",
	"[Quest_Goblin_BasicGroundRangedEnemy]",
	"[Quest_Goblin_BogMonster]",
	"[Quest_Goblin_BogMonster_Tentacle]",
	"[Quest_Goblin_EliteFlyingRangedEnemy]",
	"[Quest_Goblin_EliteGroundMeleeEnemy]",
	"[Quest_Goblin_FirePotion]",
	"[Quest_Goblin_FirePowerup]",
	"[Quest_Goblin_KnightChargeEnemy]",
	"[Quest_Goblin_KnightSpinEnemy]",
	"[Quest_Goblin_RotatingBossEnemy]",
	"[Quest_Goblin_VolleyRangedEnemy]",
	"[Quest_Goblin_Wand]",
	"[Quest_Goblin_WitchBoss]",
	"[Quest_Pirate1_BarStool]",
	"[Quest_Pirate1_BeerBottle]",
	"[Quest_Pirate1_BreakableFish]",
	"[Quest_Pirate1_CoconutBomb]",
	"[Quest_Pirate1_CoinStack_Small]",
	"[Quest_Pirate1_Cutlass]",
	"[Quest_Pirate1_Flintlock]",
	"[Quest_Pirate1_FryingPan]",
	"[Quest_Pirate1_Gibbet]",
	"[Quest_Pirate1_LootChest]",
	"[Quest_Pirate1_LostLoot]",
	"[Quest_Pirate1_Manager]",
	"[Quest_Pirate1_Mug]",
	"[Quest_Pirate1_Oar]",
	"[Quest_Pirate1_Plate]",
	"[Quest_Pirate1_PushBroom]",
	"[Quest_Pirate1_RumJug]",
	"[Quest_Pirate1_StoreLootChest]",
	"[Quest_Pirate1_Torch]",
	"[Quest_Pirate_BasicGroundMeleeEnemy]",
	"[Quest_Pirate_BossEnemy]",
	"[Quest_Pirate_CannoneerEnemy]",
	"[Quest_Pirate_Ground_Bottle_ThrownEnemy]",
	"[Quest_Pirate_Ground_Explosive_ThrownEnemy]",
	"[Quest_Pirate_Ground_RangedEnemy]",
	"[Quest_SciFi1_Manager]",
	"[Quest_SciFi_AutomaticGun]",
	"[Quest_SciFi_BasicFlyingRangedEnemy]",
	"[Quest_SciFi_BasicGroundRangedEnemy]",
	"[Quest_SciFi_EliteFlyingRangedEnemy]",
	"[Quest_SciFi_EliteGroundRangedEnemy]",
	"[Quest_Scifi_JumbotronBossEnemy]",
	"[Quest_SciFi_KnightAssassinEnemy]",
	"[Quest_SciFi_Pistol]",
	"[Quest_SciFi_RailGun]",
	"[Quest_SciFi_Shotgun]",
	"[Quest_SciFi_TinyGroundExplosiveEnemy]",
	"[Quest_Witch_Projectile]",
	"[RecRallyManager]",
	"[Sandbox_CodeOfConduct_Poster]",
	"[Sandbox_CouchChair]",
	"[Sandbox_Friendotron]",
	"[Sandbox_Lockers]",
	"[Sandbox_SnowballPile]",
	"[SciFi_Grenade]",
	"[SoccerManager]",
	"[SoccerPowerup_Star]",
	"[Soccer_SpeedPowerup]",
	"[SoloCup]",
	"[Standee_Bear01]",
	"[StNMonsterCostumeDummy]",
	"[StuntRunner_BoostManager]",
	"[StuntRunner_Manager]",
	"[StuntRunner_Wall_Long]",
	"[Trophy_Oscar]",
	"[Vehicle_50sCar]",
	"[Vehicle_RallyBuggy]",
	"[Vehicle_Truck]",
	"[Vehicle_Wolf]",
	"[VendingMachine]",
	"[Whip]"
        };

        inline int selectedprefab = 0;
        inline bool spawnasset = false;
        inline float prefabscale = 1.0f;
        inline int prefabamount = 1;
        inline std::string selectedPrefabName;
        inline Vector3f prefabpos = { 1, 1, 1 };
        inline Quaternion4f prefabrot = { 1, 1, 1, 1 };
        inline bool custompos = false;
        inline bool customrot = false;
        inline bool customscale = false;
        inline bool forceequip = false;
    }
    namespace combat
    {
        inline bool rapidfire = false;
        inline bool infiniteammo = false;
        inline bool norecoil = false;
        inline bool fastbullets = false;
        inline bool cubeofbullets = false;
        inline bool holdtofire = false;

        inline int buletamount = 1;
        inline bool custombullet = false;


    }
}