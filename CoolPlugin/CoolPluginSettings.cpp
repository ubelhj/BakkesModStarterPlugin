#include "pch.h"
#include "CoolPlugin.h"

void CoolPlugin::RenderSettings() {
    ImGui::TextUnformatted("A really cool plugin");

    if (ImGui::Button("Ball On Top")) {
        gameWrapper->Execute([this](GameWrapper* gw) {
            cvarManager->executeCommand("CoolerBallOnTop");
            });
    }
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip("Activate Ball On Top");
    }

    CVarWrapper enableCvar = cvarManager->getCvar("cool_enabled");
    if (!enableCvar) { return; }
    bool enabled = enableCvar.getBoolValue();
    if (ImGui::Checkbox("Enable plugin", &enabled)) {
        enableCvar.setValue(enabled);
    }
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip("Toggle Cool Plugin");
    }

    CVarWrapper distanceCvar = cvarManager->getCvar("cool_distance");
    if (!distanceCvar) { return; }
    float distance = distanceCvar.getFloatValue();
    if (ImGui::SliderFloat("Distance", &distance, 0.0, 500.0)) {
        distanceCvar.setValue(distance);
    }
    if (ImGui::IsItemHovered()) {
        std::string hoverText = "distance is " + std::to_string(distance);
        ImGui::SetTooltip(hoverText.c_str());
    }
}