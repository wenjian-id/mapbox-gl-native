#include "imgui_backend.hpp"

#include "imgui_backend_impl.hpp"

namespace mbgl {
namespace shell {

ImGuiBackend::ImGuiBackend(Window::Impl &windowImpl) : impl(Impl::Create(windowImpl)) {}

ImGuiBackend::~ImGuiBackend() = default;

void ImGuiBackend::newFrame() {
    impl->newFrame();
}

void ImGuiBackend::renderDrawData() {
    impl->renderDrawData();
}

} // namespace shell
} // namespace mbgl
