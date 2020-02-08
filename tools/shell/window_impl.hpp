#pragma once

#include "util.hpp"
#include "window.hpp"

#include <string>

namespace mbgl {
namespace shell {

class Window::Impl {
public:
    virtual ~Impl() {}

    // Initializes the window with the dimensions
    // and the tile when supported.
    virtual expected<bool, std::string> init(unsigned width, unsigned height, const char *title) = 0;

    // Show the window and all its children
    // widgets.
    virtual void show() = 0;

    // Factory for creating the Window, implemented
    // by backends such as GLFW and GLFM.
    static std::unique_ptr<Impl> Create(Window &parent);

protected:
    Impl(Window &parent_) : parent(parent_) {}

    Window &parent;
};

} // namespace shell
} // namespace mbgl
