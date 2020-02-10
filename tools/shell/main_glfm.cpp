#include "demo_widget.hpp"
#include "fps_widget.hpp"
#include "map_widget.hpp"
#include "window.hpp"

#include <glfm.h>

static void onFrame(GLFMDisplay *display, const double frameTime);
static void onSurfaceCreated(GLFMDisplay *display, const int width, const int height);
static void onSurfaceDestroyed(GLFMDisplay *display);

void glfmMain(GLFMDisplay *display) {
    mbgl::shell::Window window;
    mbgl::shell::MapWidget map(window);
    mbgl::shell::FPSWidget fps(window);
    mbgl::shell::DemoWidget demo(window);

    window.show();

    glfmSetDisplayConfig(display,
                         GLFMRenderingAPIOpenGLES2,
                         GLFMColorFormatRGBA8888,
                         GLFMDepthFormatNone,
                         GLFMStencilFormatNone,
                         GLFMMultisampleNone);

    glfmSetSurfaceCreatedFunc(display, onSurfaceCreated);
    glfmSetSurfaceResizedFunc(display, onSurfaceCreated);
    glfmSetSurfaceDestroyedFunc(display, onSurfaceDestroyed);
    glfmSetMainLoopFunc(display, onFrame);
}

static void onSurfaceCreated(GLFMDisplay *, const int width, const int height) {
    glViewport(0, 0, width, height);
}

static void onSurfaceDestroyed(GLFMDisplay *) {
}

static void onFrame(GLFMDisplay *, const double) {
    glClearColor(0.4f, 0.0f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
