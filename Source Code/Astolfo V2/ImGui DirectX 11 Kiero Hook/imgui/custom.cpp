#include "custom.h"
#include "imgui.h"
#include "imgui_internal.h"
#include <map>

struct checkbox_animation {
    float animation;
};

bool ImGui::Custom::Toggle(const char* label, bool* v) {
    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label);
    const ImVec2 label_size = CalcTextSize(label, NULL, true);
    const float square_sz = 17;
    const float spacing = 6;
    const ImVec2 pos = window->DC.CursorPos;

    // Frame rectangle for the toggle
    const ImRect frame_bb(pos, ImVec2(pos.x + square_sz * 2.0f, pos.y + square_sz));
    const ImRect total_bb(pos, ImVec2(pos.x + square_sz * 2.0f + spacing + label_size.x, pos.y + square_sz));

    ItemSize(total_bb, style.FramePadding.y);
    if (!ItemAdd(total_bb, id))
        return false;

    bool hovered, held;
    bool pressed = ButtonBehavior(frame_bb, id, &hovered, &held);
    if (pressed) {
        *v = !(*v);
        MarkItemEdited(id);
    }

    // Animation map
    static std::map<ImGuiID, checkbox_animation> anim;
    auto it_anim = anim.find(id);
    if (it_anim == anim.end()) {
        anim.insert({ id, { 0.0f } });
        it_anim = anim.find(id);
    }

    // Smooth animation
    float delta_time = ImGui::GetIO().DeltaTime;
    float lerp_factor = 1.0f - ImPow(0.88f, delta_time * 60.0f);
    it_anim->second.animation = ImLerp(it_anim->second.animation, *v ? 1.0f : 0.0f, lerp_factor);

    RenderNavHighlight(total_bb, id);

    ImVec2 toggle_min = frame_bb.Min;
    ImVec2 toggle_max = ImVec2(frame_bb.Min.x + 30.0f, frame_bb.Min.y + 15.0f);

    // Background OFF (darker gray)
    RenderFrame(toggle_min, toggle_max, ImColor(0.12f, 0.12f, 0.12f, 1.0f), false, 9.0f);

    // Background ON (pinkish-purple) with animation
    RenderFrame(toggle_min, toggle_max, ImColor(0.847f, 0.631f, 0.988f, it_anim->second.animation), false, 9.0f);

    // Toggle knob (white)
    window->DrawList->AddCircleFilled(
        ImVec2(toggle_min.x + 7 + 14 * it_anim->second.animation, toggle_min.y + 7),
        5.0f,
        ImColor(1.0f, 1.0f, 1.0f),
        30
    );

    // Draw label
    if (label_size.x > 0.0f)
        RenderText(ImVec2(toggle_max.x + spacing, pos.y + 1), label);

    return pressed;
}
