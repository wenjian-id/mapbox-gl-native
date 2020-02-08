#include "imgui_backend_impl.hpp"

#include "window_impl_glfw.hpp"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace mbgl {
namespace shell {

class ImGuiBackendImplGLFW final : public ImGuiBackend::Impl {
public:
    ImGuiBackendImplGLFW(Window::Impl &windowImpl);
    ~ImGuiBackendImplGLFW();

    void newFrame() override;
    void renderDrawData() override;
};

ImGuiBackendImplGLFW::ImGuiBackendImplGLFW(Window::Impl &windowImpl) {
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(static_cast<WindowImplGLFW &>(windowImpl).getGLFWwindow(), true);
    ImGui_ImplOpenGL3_Init();
}

ImGuiBackendImplGLFW::~ImGuiBackendImplGLFW() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiBackendImplGLFW::newFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiBackendImplGLFW::renderDrawData() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

// static
std::unique_ptr<ImGuiBackend::Impl> ImGuiBackend::Impl::Create(Window::Impl &windowImpl) {
    return std::make_unique<ImGuiBackendImplGLFW>(windowImpl);
}

} // namespace shell
} // namespace mbgl
