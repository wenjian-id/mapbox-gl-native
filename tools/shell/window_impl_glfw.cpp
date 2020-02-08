#include "window_impl_glfw.hpp"

namespace mbgl {
namespace shell {

WindowImplGLFW::WindowImplGLFW(Window &parent_) : Window::Impl(parent_) {}

WindowImplGLFW::~WindowImplGLFW() {
    glfwDestroyWindow(glfwWindow);
    glfwTerminate();
}

expected<bool, std::string> WindowImplGLFW::init(unsigned width, unsigned height, const char *title) {
    if (!glfwInit()) {
        return unexpected<std::string>("GLFW not initialized.");
    }

    glfwWindow = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!glfwWindow) {
        return unexpected<std::string>("Could not create GLFW window.");
    }

    glfwMakeContextCurrent(glfwWindow);
    glfwSwapInterval(1);

    return true;
}

void WindowImplGLFW::show() {
    while (!glfwWindowShouldClose(glfwWindow)) {
        glfwPollEvents();

        int w, h;
        glfwGetFramebufferSize(glfwWindow, &w, &h);
        glViewport(0, 0, w, h);

        // TODO: Only resize when needed.
        parent.resize(w, h);
        parent.render();

        glfwSwapBuffers(glfwWindow);
    }
}

// static
std::unique_ptr<Window::Impl> Window::Impl::Create(Window &parent) {
    return std::make_unique<WindowImplGLFW>(parent);
}

} // namespace shell
} // namespace mbgl
