#pragma once

#include "window_impl.hpp"

namespace mbgl {
namespace shell {

class WindowImplGLFM final : public Window::Impl {
public:
    WindowImplGLFM(Window &parent);
    ~WindowImplGLFM();

    expected<bool, std::string> init(unsigned width, unsigned height, const char *title) override;
    void show() override;
};

} // namespace shell
} // namespace mbgl
