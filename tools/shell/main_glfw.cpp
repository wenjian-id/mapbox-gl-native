#include "demo_widget.hpp"
#include "fps_widget.hpp"
#include "map_widget.hpp"
#include "window.hpp"

int main(int, char **) {
    mbgl::shell::Window window;
    mbgl::shell::MapWidget map(window);
    mbgl::shell::FPSWidget fps(window);
    mbgl::shell::DemoWidget demo(window);

    window.show();

    return 0;
}
