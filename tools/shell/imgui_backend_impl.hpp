#pragma once

#include "imgui_backend.hpp"

#include <string>

namespace mbgl {
namespace shell {

class ImGuiBackend::Impl {
public:
    virtual ~Impl() = default;

    virtual void newFrame() = 0;
    virtual void renderDrawData() = 0;

    // Factory for creating the ImGuiBackend, to abstract
    // integration with the window system and graphics
    // backend such as OpenGL and Metal.
    static std::unique_ptr<Impl> Create(Window::Impl &windowImpl);

protected:
    Impl() = default;
};

} // namespace shell
} // namespace mbgl
