#include "fps_widget.hpp"

#include <imgui.h>

namespace mbgl {
namespace shell {

FPSWidget::FPSWidget(Window& parent_) : Widget(parent_) {}

void FPSWidget::render() {
    constexpr auto overlay = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize |
                             ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::Begin("overlay", nullptr, overlay);
    ImGui::Text("FPS %.1f", ImGui::GetIO().Framerate);
    ImGui::End();
}

} // namespace shell
} // namespace mbgl
