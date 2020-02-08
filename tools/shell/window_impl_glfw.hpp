#pragma once

#include "window_impl.hpp"

#include <GLFW/glfw3.h>

namespace mbgl {
namespace shell {

class WindowImplGLFW final : public Window::Impl {
public:
    WindowImplGLFW(Window &parent);
    ~WindowImplGLFW();

    expected<bool, std::string> init(unsigned width, unsigned height, const char *title) override;
    void show() override;

    GLFWwindow *getGLFWwindow() { return glfwWindow; }

private:
    GLFWwindow *glfwWindow = nullptr;
};

} // namespace shell
} // namespace mbgl
