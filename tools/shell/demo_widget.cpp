#include "demo_widget.hpp"

#include <imgui.h>

namespace mbgl {
namespace shell {

DemoWidget::DemoWidget(Window& parent_) : Widget(parent_) {}

void DemoWidget::render() {
    if (visible) {
        ImGui::ShowDemoWindow(&visible);
    }
}

} // namespace shell
} // namespace mbgl
