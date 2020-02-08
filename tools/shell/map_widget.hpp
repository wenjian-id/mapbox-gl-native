#pragma once

#include "widget.hpp"

namespace mbgl {
namespace shell {

class MapWidget final : public Widget {
public:
    MapWidget(Window &window);

protected:
    void render() override;
};

} // namespace shell
} // namespace mbgl
