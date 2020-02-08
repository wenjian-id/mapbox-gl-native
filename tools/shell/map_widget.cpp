#include "map_widget.hpp"

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

namespace mbgl {
namespace shell {

MapWidget::MapWidget(Window &parent_) : Widget(parent_) {}

void MapWidget::render() {
    glClearColor(0.4f, 0.0f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

} // namespace shell
} // namespace mbgl
