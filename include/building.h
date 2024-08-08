#ifndef BUILDING_H
#define BUILDING_H

#include <string>

class Building {
public:
    Building(const std::string &type, const std::string &material, const std::string &geographicalArea, int floors, int capacity);

    std::string getType() const;
    std::string getMaterial() const;
    std::string getGeographicalArea() const;
    int getFloors() const;
    int getCapacity() const;

private:
    std::string type;
    std::string material;
    std::string geographicalArea;
    int floors;
    int capacity;
};

#endif // BUILDING_H
