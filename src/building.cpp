#include "building.h"

Building::Building(const std::string &type, const std::string &material, const std::string &geographicalArea, int floors, int capacity)
    : type(type), material(material), geographicalArea(geographicalArea), floors(floors), capacity(capacity) {}

std::string Building::getType() const {
    return type;
}

std::string Building::getMaterial() const {
    return material;
}

std::string Building::getGeographicalArea() const {
    return geographicalArea;
}

int Building::getFloors() const {
    return floors;
}

int Building::getCapacity() const {
    return capacity;
}
