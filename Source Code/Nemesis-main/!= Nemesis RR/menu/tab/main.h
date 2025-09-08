#pragma once
#include "../../includes.h"
#include "inc.h"
void MainTab()
{

    GradientText("Main", 0.7f, lightBlue, darkBlue);
    ImGui::Separator();

    ImGui::Checkbox("FOV Changer", &UI::Engine::FOV);
    if (UI::Engine::FOV)
    {
        if (GetAsyncKeyState('R') & 0x8000)
        {
            ImGui::SliderFloat("FOV", &UI::Engine::PlayerFOV, 1.0f, 200.0f, "%.1f");
        }
        else
        {
            ImGui::SliderFloat("FOV", &UI::Engine::RealFOV, 1.0f, 200.0f, "%.1f");
        }
    }
    ImGui::Checkbox("Dynamic Fly", &UI::Movement::DynamicFly);
    ImGui::Checkbox("Clothing", &UI::Wardrobe::ItemUnlocker);
    ImGui::Checkbox("Airstuck", &UI::Engine::EnableAirstuck);



    GradientText("Network", 0.7f, lightBlue, darkBlue);
    ImGui::Separator();
    ImGui::Checkbox("Maker Pen", &UI::MakerPen::MakerPen);
    ImGui::Checkbox("Spawn Invention", &UI::MakerPen::SpawnInvention);
    ImGui::Checkbox("Ink Limit Bypass", &UI::MakerPen::InkLimit); //doesnt work ffs




    GradientText("idefk", 0.7f, lightBlue, darkBlue);
    ImGui::Separator();
    ImGui::Checkbox("Developer Hooks", &UI::DeveloperUI::developer);




    GradientText("Player", 0.7f, lightBlue, darkBlue);
    ImGui::Separator();
    ImGui::Checkbox("Self Revive", &UI::Health::SelfRevive);
    ImGui::Checkbox("Head Scaling", &UI::Player::Head::HeadScaling);
    if (UI::Player::Head::HeadScaling)
    {
        ImGui::SliderFloat("Head Scale", &UI::Player::Head::HScale, 0.1f, 15.0f);
    }




    GradientText("Weapon", 0.7f, lightBlue, darkBlue);
    ImGui::Separator();
    ImGui::Checkbox("Rapid Fire", &UI::Weapon::NoCoolDown);
    ImGui::Checkbox("infinite Ammo", &UI::Weapon::InfiniteAmmo);




    GradientText("Quest", 0.7f, lightBlue, darkBlue);
    ImGui::Separator();
    ImGui::Checkbox("Quest Godmode", &UI::Health::QuestGodmode);
    ImGui::Checkbox("Point Multiplier", &UI::Quests::Points::QuestPointsModifier);
    if (UI::Quests::Points::QuestPointsModifier)
    {
        ImGui::SliderInt("P Amount", &UI::Quests::Points::QuestPointsInt, 1, 100000);
    }

    ImGui::Checkbox("Gold/Silver Multiplier", &UI::Quests::Points::QuestGoldModifier);
    if (UI::Quests::Points::QuestGoldModifier)
    {
        ImGui::SliderInt("G/S Amount", &UI::Quests::Points::QuestGoldInt, 1, 100000);
    }
    ImGui::Checkbox("Golden Trophy", &UI::Quests::Skip::SkipGoldenTrophy);
    ImGui::Checkbox("Crimson Cauldron", &UI::Quests::Skip::SkipCrims);
    ImGui::Checkbox("Jumbotron", &UI::Quests::Skip::SkipJumbotron);
    ImGui::Checkbox("Isle Of Lost Skulls", &UI::Quests::Skip::SkipIsle);
    ImGui::Checkbox("Cresendo", &UI::Quests::Skip::SkipCresendo);;
    ImGui::Checkbox("Skip Boss", &UI::Quests::Skip::SkipBoss);
    ImGui::Checkbox("Custom Skip", &UI::Quests::Skip::CustomSkip);
    if (UI::Quests::Skip::CustomSkip)
        ImGui::SliderInt("Rooms To Skip", &UI::Quests::Skip::CustomSkipper, 1, 99);

}