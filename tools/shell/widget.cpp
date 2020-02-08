#include "widget.hpp"

namespace mbgl {
namespace shell {

Widget::Widget(Window &parent_) : parent(parent_) {
    parent.addWidget(*this);
}

Widget::~Widget() {
    parent.removeWidget(*this);
}

} // namespace shell
} // namespace mbgl
