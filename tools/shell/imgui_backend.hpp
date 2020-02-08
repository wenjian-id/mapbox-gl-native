#pragma once

#include "window_impl.hpp"

#include <memory>

namespace mbgl {
namespace shell {

class ImGuiBackend final {
public:
    ImGuiBackend(Window::Impl &);
    ~ImGuiBackend();

    // Starts a new ImGui frame.
    void newFrame();

    // Create the draw calls and render
    // the frame using the graphics backend.
    void renderDrawData();

    class Impl;

private:
    std::unique_ptr<Impl> impl;
};

} // namespace shell
} // namespace mbgl
