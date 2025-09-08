#pragma once
#include <Windows.h>
#include "xorstr.hpp"
#include <vector>
#include <mutex>





namespace UI
{
	bool Watermark = true;
	bool show = true;
	int tab = 0;





	namespace Engine {
		bool EnableAirstuck = false;
		bool Airstuck = false;
		bool MasterKill = false;

		// Time control
		bool TimeScale = false;
		float TimeFloat = 1.0f;

		// FOV and aspect

		bool FOV = false;

		float PlayerFOV = 68.0f;
		float FOVOverride = 40.0f;
		static float RealFOV = PlayerFOV;
		bool aspectRation = false;
		float floataspect = 100.0f;

		// Full bright
		bool FullBright = false;
	}

	namespace Movement {
		bool DynamicFly = false;
		bool StaticFly = false;
	}

	namespace Wardrobe {
		bool ItemUnlocker = false;
	}

	namespace MakerPen {
		bool MakerPen = false;
		bool SpawnInvention = false;
		bool InkLimit = false;
	}

	namespace DeveloperUI {
		bool developer = false;
	}

	namespace Weapon {
		bool NoCoolDown = false;
		bool InfiniteAmmo = false;
	}

	namespace BulletModifier {
		bool BulletToggle = false;
		int BulletAmount = 1;
	}

	namespace Health {
		bool SelfRevive = false;
		bool QuestGodmode = false;
	}

	namespace Player {
		namespace Head {
			bool HeadScaling = false;
			float HScale = 1.0f;
		}

		namespace Body {
			bool SelfScaling = false;
		}
	}

	namespace FoodExploit {
		bool FoodSettings = false;
		bool FoodSwap = false;
		float FoodScale = 1.0f;
		int FoodInt = 1;
		static char searchBuffer[64] = "";
		int selectedIndex = -1;
	}

	namespace Quests {
		namespace Points {
			bool QuestPointsModifier = false;
			int QuestPointsInt = 1;
			bool QuestGoldModifier = false;
			int QuestGoldInt = 1;
		}

		namespace Skip {
			bool SkipGoldenTrophy = false;
			bool SkipCrims = false;
			bool SkipJumbotron = false;
			bool SkipIsle = false;
			bool SkipCresendo = false;
			bool SkipBoss = false;
			bool CustomSkip = false;
			int CustomSkipper = 1;
		}
	}

	namespace Settings {
		bool EnableDiscord = true;
	}
}

// food Sploit Shit
typedef struct Food
{
	const char* frie;
	const char* guid;
} Food;
//  Food Liste (NEW)
Food Guid[]
{
	{ "87 Flavor Cake", "xwQWBB_fekmTqRc2LB92cg" },
	{ "Assorted Donuts", "ZuvkidodzkuOfGLDnTOFyg" },
	{ "Bubbly Classic", "iiGTvhOCHkOTNJhb16Zbyw" },
	{ "Candy Apples", "EmPvh3I6L0uK_1i8Wy_ylQ" },
	{ "Celebration Cake", "Sk_1sm88ZU2zpWn01Lv7hw" },
	{ "Cheese Pizza", "5hIAZ9wg5EyG1cILf4FS2A" },
	{ "Chocolate Cake", "BbJb1_0g4EGJP_CeNrjpew" },
	{ "Chocolate Frosted Donuts", "mMCGPgK3tki5S_15q2Z81A" },
	{ "Chocolate Variety Box", "K9RbXo-4U0q6NbGu8VL1Sw" },
	{ "Classic Popcorn", "QRx0aSTT9keMFdAJMQHdTg" },
	{ "Glazed Donuts", "7OZ5AE3uuUyqa0P-2W1ptg" },
	{ "Hawaiian Pizza", "_jnjYGBcyEWY5Ub4OezXcA" },
	{ "Latte", "P15H1ONBhk-5DYYjid1ttg" },
	{ "Pepperoni Pizza", "mq23W-RSP0G8iGNLdrcpUw" },
	{ "Red Apples", "uMHrUPLYFk2rJOW_uop5Aw" },
	{ "Red Velvet Cake", "LwaotjVEBUir0-w8126n_g" },
	{ "Root Beer", "JfnVXFmilU6ysv-VbTAe3A" },
	{ "Salted Pretzels", "InQ25wQMGkG_bvuD5rf2Ag" },
	//{ "Testing", "[Bucket]" },
	{ "Supreme Pizza", "wUCIKdJSvEmiQHYMyx4X4w" },
};

const char* SelectedFood;
int FoodF = sizeof(Guid) / sizeof(Guid[0]);