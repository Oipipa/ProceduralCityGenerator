#ifndef CITY_GENERATOR_H
#define CITY_GENERATOR_H

#include "lsystem.h"
#include "building.h"
#include "geographical_feature.h"
#include "road_network.h"
#include <vector>
#include <string>
#include <map>

class CityGenerator {
public:
    CityGenerator();
    void generateCity(int iterations);
    void printCity() const;
    void saveCityToROOT(const std::string &filename) const;

private:
    void processSymbol(char symbol, const std::string &area);
    void generateTerrain();
    void arrangeBuildingsAndFeatures();
    std::vector<Building> cityMap;
    std::vector<GeographicalFeature> geographicalFeatures;
    LSystem lsystem;
    RoadNetwork roadNetwork;
    std::vector<std::string> geographicalAreas;
    std::vector<std::string> materials;
    std::map<std::string, std::vector<std::string>> areaSpecificTrees;
    std::map<std::string, std::vector<std::string>> areaSpecificPlants;
    std::map<std::string, int> areaSpecificBuildingFloors;
    std::map<std::string, int> areaSpecificBuildingCapacities;
    std::map<std::string, std::vector<std::string>> areaSpecificBuildingTypes;
    std::map<std::string, int> areaPopulationDensity;
    std::map<std::string, double> areaSpecificPopulations;
    std::map<std::string, std::vector<std::string>> terrainConstraints;
};

#endif // CITY_GENERATOR_H
