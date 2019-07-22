#include <mbgl/style/conversion_impl.hpp>
#include <mbgl/style/expression/compound_expression.hpp>
#include <mbgl/style/expression/dsl.hpp>
#include <mbgl/style/expression/expression.hpp>
#include <mbgl/style/expression/literal.hpp>
#include <mbgl/style/expression/parsing_context.hpp>
#include <mbgl/style/property_expression.hpp>
#include <mbgl/style/sources/geojson_source_impl.hpp>
#include <mbgl/tile/tile_id.hpp>
#include <mbgl/util/constants.hpp>
#include <mbgl/util/string.hpp>
#include <rapidjson/document.h>
#include <rapidjson/error/en.h>

#include <mapbox/geojsonvt.hpp>
#include <supercluster.hpp>
#include <mbgl/style/conversion/json.hpp>
#include <mbgl/style/conversion/constant.hpp>
#include <mbgl/style/conversion/property_value.hpp>
#include <mbgl/style/expression/dsl.hpp>

#include <cmath>
#include <functional>

namespace mbgl {
namespace style {

class GeoJSONVTData : public GeoJSONData {
public:
    GeoJSONVTData(const GeoJSON& geoJSON, const mapbox::geojsonvt::Options& options)
        : impl(geoJSON, options) {
    }

    mapbox::feature::feature_collection<int16_t> getTile(const CanonicalTileID& tileID) final {
        return impl.getTile(tileID.z, tileID.x, tileID.y).features;
    }

    mapbox::feature::feature_collection<double> getChildren(const std::uint32_t) final {
        return {};
    }

    mapbox::feature::feature_collection<double>
    getLeaves(const std::uint32_t, const std::uint32_t, const std::uint32_t) final {
        return {};
    }

    std::uint8_t getClusterExpansionZoom(std::uint32_t) final {
        return 0;
    }

private:
    mapbox::geojsonvt::GeoJSONVT impl;
};

class SuperclusterData : public GeoJSONData {
public:
    SuperclusterData(const mapbox::feature::feature_collection<double>& features,
                     const mapbox::supercluster::Options& options)
        : impl(features, options) {
    }

    mapbox::feature::feature_collection<int16_t> getTile(const CanonicalTileID& tileID) final {
        return impl.getTile(tileID.z, tileID.x, tileID.y);
    }

    mapbox::feature::feature_collection<double> getChildren(const std::uint32_t cluster_id) final {
        return impl.getChildren(cluster_id);
    }

    mapbox::feature::feature_collection<double> getLeaves(const std::uint32_t cluster_id,
                                                          const std::uint32_t limit,
                                                          const std::uint32_t offset) final {
        return impl.getLeaves(cluster_id, limit, offset);
    }

    std::uint8_t getClusterExpansionZoom(std::uint32_t cluster_id) final {
        return impl.getClusterExpansionZoom(cluster_id);
    }

private:
    mapbox::supercluster::Supercluster impl;
};

GeoJSONSource::Impl::Impl(std::string id_, GeoJSONOptions options_)
    : Source::Impl(SourceType::GeoJSON, std::move(id_)), options(std::move(options_)) {
}

std::unique_ptr<style::expression::Expression>
createExpression(const char* op, std::vector<std::unique_ptr<style::expression::Expression>> args) {
    style::expression::ParsingContext ctx;
    style::expression::ParseResult result =
        style::expression::createCompoundExpression(op, std::move(args), ctx);
    assert(result);
    return std::move(*result);
}

GeoJSONSource::Impl::Impl(const Impl& other, const GeoJSON& geoJSON)
    : Source::Impl(other), options(other.options) {
    constexpr double scale = util::EXTENT / util::tileSize;

    if (options.cluster && geoJSON.is<mapbox::feature::feature_collection<double>>() &&
        !geoJSON.get<mapbox::feature::feature_collection<double>>().empty()) {
        mapbox::supercluster::Options clusterOptions;
        clusterOptions.maxZoom = options.clusterMaxZoom;
        clusterOptions.extent = util::EXTENT;
        clusterOptions.radius = ::round(scale * options.clusterRadius);
        // process here, taking the cluster propeties into consideration
        
        using namespace mbgl::style::expression::dsl;
        using namespace mbgl;
        using namespace mbgl::style;

      using JSValue = rapidjson::GenericValue<rapidjson::UTF8<>, rapidjson::CrtAllocator>;

        
//        std::unordered_map<std::string, const char*>
//        properties{{std::string("max"), expr1}};
        const char* expr1 = R"(["get", "scalerank"])";
        rapidjson::GenericDocument<rapidjson::UTF8<>, rapidjson::CrtAllocator> document;
        document.Parse<0>(expr1);
        assert(!document.HasParseError());
        expression::ParsingContext ctx;
//        optional<expression::TypeAnnotationOption> typeAnnotationOption;
        const JSValue* expression = &document;
        expression::ParseResult parsed = ctx.parseExpression(mbgl::style::conversion::Convertible(expression));
        auto mapExpression = PropertyExpression<double>(std::move(*parsed));
        
        const char* expr2 = R"(["+",["accumulated"], ["get", "max"]])";
        rapidjson::GenericDocument<rapidjson::UTF8<>, rapidjson::CrtAllocator> document2;
        document2.Parse<0>(expr2);
        assert(!document2.HasParseError());
        expression::ParsingContext ctx2;
        //        optional<expression::TypeAnnotationOption> typeAnnotationOption;
        const JSValue* expression2 = &document2;
        expression::ParseResult parsed2 = ctx.parseExpression(mbgl::style::conversion::Convertible(expression2));
        auto reduceExpression = PropertyExpression<double>(std::move(*parsed2));
        
        
//        auto mapExpression = PropertyExpression<double>(get("scalerank"));
//        auto reduceExpression = PropertyExpression<double>(get("max"));
         clusterOptions.map = [&](const mapbox::feature::property_map& properties) ->
        mapbox::feature::property_map {mapbox::feature::property_map ret{};
            auto feature = mapbox::feature::feature<double>();
            feature.properties = properties;
            ret["max"] = mapExpression.evaluate(feature);
            return ret;
        };
        clusterOptions.reduce = [&](mapbox::feature::property_map & toReturn, const mapbox::feature::property_map &toFill){
            auto feature = mapbox::feature::feature<double>();
            feature.properties = toFill;
            toReturn["max"] = reduceExpression.evaluate( feature);
        };
        data = std::make_shared<SuperclusterData>(
            geoJSON.get<mapbox::feature::feature_collection<double>>(), clusterOptions);
    } else {
        mapbox::geojsonvt::Options vtOptions;
        vtOptions.maxZoom = options.maxzoom;
        vtOptions.extent = util::EXTENT;
        vtOptions.buffer = ::round(scale * options.buffer);
        vtOptions.tolerance = scale * options.tolerance;
        vtOptions.lineMetrics = options.lineMetrics;
        data = std::make_shared<GeoJSONVTData>(geoJSON, vtOptions);
    }
}

GeoJSONSource::Impl::~Impl() = default;

Range<uint8_t> GeoJSONSource::Impl::getZoomRange() const {
    return { options.minzoom, options.maxzoom };
}

std::weak_ptr<GeoJSONData> GeoJSONSource::Impl::getData() const {
    return data;
}

optional<std::string> GeoJSONSource::Impl::getAttribution() const {
    return {};
}

} // namespace style
} // namespace mbgl
