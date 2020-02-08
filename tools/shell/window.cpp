#include "window.hpp"

#include "imgui_backend.hpp"
#include "widget.hpp"
#include "window_impl.hpp"

#include <imgui.h>

#include <iostream>
#include <memory>

namespace mbgl {
namespace shell {

Window::Window() : impl(Impl::Create(*this)) {
    auto expected = impl->init(800, 600, "Mapbox GL Shell");
    if (!expected) {
        std::cerr << expected.error() << std::endl;
        errored = true;
        return;
    }

    IMGUI_CHECKVERSION();

    imgui = std::make_unique<ImGuiBackend>(*impl);

    ImGui::StyleColorsDark();
    ImGui::GetIO().IniFilename = nullptr;
}

Window::~Window() {
    if (errored) {
        return;
    }
}

void Window::addWidget(Widget &widget) {
    children.push_back(&widget);
}

void Window::removeWidget(Widget &widget) {
    children.remove(&widget);
}

void Window::show() {
    if (errored) {
        return;
    }

    for (auto widget : children) {
        widget->show();
    }

    impl->show();
}

void Window::render() {
    imgui->newFrame();

    for (auto widget : children) {
        if (widget->isVisible()) {
            widget->render();
        }
    }

    imgui->renderDrawData();
}

void Window::resize(unsigned width, unsigned height) {
    ImGuiIO &io = ImGui::GetIO();

    io.DisplaySize = ImVec2(width, height);
    io.DisplayFramebufferScale = ImVec2(1, 1);

    for (auto widget : children) {
        widget->resize(width, height);
    }
}

} // namespace shell
} // namespace mbgl
