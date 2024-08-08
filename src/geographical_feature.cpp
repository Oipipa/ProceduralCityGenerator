#include "geographical_feature.h"

GeographicalFeature::GeographicalFeature(const std::string &type, const std::string &details, const std::string &area)
    : type(type), details(details), area(area) {}

std::string GeographicalFeature::getType() const {
    return type;
}

std::string GeographicalFeature::getDetails() const {
    return details;
}

std::string GeographicalFeature::getArea() const {
    return area;
}
