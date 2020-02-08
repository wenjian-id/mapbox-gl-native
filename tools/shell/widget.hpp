#pragma once

#include "window.hpp"

#include <utility>

namespace mbgl {
namespace shell {

class Widget {
public:
    Widget(Window &parent);
    virtual ~Widget();

    // Function called when the widget is about
    // to be visible. It will be called with a
    // valid graphics context.
    virtual void show() {}

    // Hide the widget, effectively it will make
    // it not render and resize anymore.
    virtual void hide() {}

    // Function called every time the widget needs
    // to render a frame. It will provide a valid
    // context for drawing and it will swap buffers
    // after this function returns. Other widgets
    // might render after or before this call, so
    // it should not assume any graphics context state.
    virtual void render() {}

    // Resize the widget taking into consideration
    // the framebuffer scale.
    virtual void resize(unsigned /* width */, unsigned /* height */) {}

    // Returns true if the widget is visible,
    // false otherwise. Invisible widgets will
    // not have render() and resize() called.
    virtual bool isVisible() const { return true; }

private:
    Window &parent;
};

} // namespace shell
} // namespace mbgl
