#pragma once

#include "widget.hpp"

namespace mbgl {
namespace shell {

class DemoWidget final : public Widget {
public:
    DemoWidget(Window &window);

    bool isVisible() const override { return visible; }
    void render() override;

private:
    bool visible = true;
};

} // namespace shell
} // namespace mbgl
