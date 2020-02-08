#pragma once

#include "widget.hpp"

namespace mbgl {
namespace shell {

class FPSWidget final : public Widget {
public:
    FPSWidget(Window &window);

protected:
    void render() override;
};

} // namespace shell
} // namespace mbgl
