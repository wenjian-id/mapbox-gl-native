#pragma once

#include <list>
#include <memory>

namespace mbgl {
namespace shell {

class ImGuiBackend;
class Widget;

class Window final {
public:
    Window();
    ~Window();

    void addWidget(Widget &widget);
    void removeWidget(Widget &widget);

    // Show the window and pools for events, it will
    // block on GLFW, and on GLFM it will be no-op.
    void show();

    // Render the window and all its visible widgets.
    void render();

    // Resize the window and the contents inside it.
    void resize(unsigned width, unsigned height);

    class Impl;

private:
    std::unique_ptr<Impl> impl;
    std::unique_ptr<ImGuiBackend> imgui;

    bool errored = false;
    std::list<Widget *> children;
};

} // namespace shell
} // namespace mbgl
