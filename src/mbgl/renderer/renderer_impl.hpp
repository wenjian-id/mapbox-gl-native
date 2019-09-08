#pragma once

#include <mbgl/renderer/render_orchestrator.hpp>

#include <memory>
#include <string>

namespace mbgl {

class RendererObserver;
class RenderStaticData;
class RenderTree;

namespace gfx {
class RendererBackend;
} // namespace gfx

class Renderer::Impl {
public:
    Impl(gfx::RendererBackend&,
         float pixelRatio_,
         optional<std::string> localFontFamily_);
    ~Impl();

    // TODO: Move orchestrator to Map::Impl.
    RenderOrchestrator orchestrator;
    void render(const RenderTree&);
    std::shared_ptr<RenderStaticData> staticData;
private:
    friend class Renderer;

    void setObserver(RendererObserver*);


    void reduceMemoryUse();


    gfx::RendererBackend& backend;

    RendererObserver* observer;

    const float pixelRatio;

    enum class RenderState {
        Never,
        Partial,
        Fully,
    };

    RenderState renderState = RenderState::Never;
};

} // namespace mbgl
