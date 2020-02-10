#include "imgui_backend_impl.hpp"

#include "window_impl_glfm.hpp"

#include <imgui.h>
#include <imgui_impl_opengl3.h>

#include <chrono>

namespace mbgl {
namespace shell {

class ImGuiBackendImplGLFM final : public ImGuiBackend::Impl {
public:
    ImGuiBackendImplGLFM(Window::Impl &windowImpl);
    ~ImGuiBackendImplGLFM();

    void newFrame() override;
    void renderDrawData() override;
};

ImGuiBackendImplGLFM::ImGuiBackendImplGLFM(Window::Impl &) {
    ImGui::CreateContext();
    ImGui_ImplOpenGL3_Init();
}

ImGuiBackendImplGLFM::~ImGuiBackendImplGLFM() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiBackendImplGLFM::newFrame() {
    static auto previousTime = std::chrono::high_resolution_clock::now();

    auto currentTime = std::chrono::high_resolution_clock::now();
    auto delta = std::chrono::duration<double>(currentTime - previousTime).count();

    ImGui::GetIO().DeltaTime = delta > 0.0f ? delta : 1.0f / 60.0f;
    previousTime = currentTime;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
}

void ImGuiBackendImplGLFM::renderDrawData() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

// static
std::unique_ptr<ImGuiBackend::Impl> ImGuiBackend::Impl::Create(Window::Impl &windowImpl) {
    return std::make_unique<ImGuiBackendImplGLFM>(windowImpl);
}

} // namespace shell
} // namespace mbgl
