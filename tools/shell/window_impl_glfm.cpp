#include "window_impl_glfm.hpp"

namespace mbgl {
namespace shell {

WindowImplGLFM::WindowImplGLFM(Window &parent_) : Window::Impl(parent_) {}

WindowImplGLFM::~WindowImplGLFM() {}

expected<bool, std::string> WindowImplGLFM::init(unsigned, unsigned, const char *) {
    return true;
}

void WindowImplGLFM::show() {}

// static
std::unique_ptr<Window::Impl> Window::Impl::Create(Window &parent) {
    return std::make_unique<WindowImplGLFM>(parent);
}

} // namespace shell
} // namespace mbgl
