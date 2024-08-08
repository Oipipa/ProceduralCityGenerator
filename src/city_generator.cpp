#include "city_generator.h"
#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <cstdlib>
#include <cmath>
#include <filesystem>
#include <algorithm>

CityGenerator::CityGenerator() : lsystem("A") {
    // Define L-system rules
    lsystem.addRule('A', "ABCPDRTUVWXY");
    lsystem.addRule('B', "EA");
    lsystem.addRule('C', "F");
    lsystem.addRule('D', "GA");
    lsystem.addRule('E', "H");
    lsystem.addRule('F', "I");
    lsystem.addRule('G', "J");
    lsystem.addRule('H', "K");
    lsystem.addRule('I', "L");
    lsystem.addRule('J', "M");
    lsystem.addRule('K', "N");
    lsystem.addRule('L', "O");
    lsystem.addRule('M', "P");
    lsystem.addRule('R', "S");
    lsystem.addRule('T', "U");
    lsystem.addRule('U', "V");
    lsystem.addRule('V', "W");
    lsystem.addRule('W', "X");
    lsystem.addRule('X', "Y");

    // Define geographical areas, materials, trees, and plants
    geographicalAreas = {"Downtown", "Suburban", "Industrial", "Park", "Hill", "Mountain", "River", "Lake", "Forest", "Wetland"};
    materials = {"Concrete", "Steel", "Wood", "Glass"};

    // Define area-specific trees and plants
    areaSpecificTrees = {
        {"Downtown", {"Oak"}},
        {"Suburban", {"Pine", "Maple"}},
        {"Industrial", {"Birch"}},
        {"Park", {"Oak", "Maple", "Birch"}},
        {"Hill", {"Pine"}},
        {"Mountain", {"Pine", "Birch"}},
        {"River", {"Willow"}},
        {"Lake", {"Cypress"}},
        {"Forest", {"Fir", "Spruce", "Pine"}},
        {"Wetland", {"Mangrove"}}
    };

    areaSpecificPlants = {
        {"Downtown", {"Grass"}},
        {"Suburban", {"Bush", "Flower"}},
        {"Industrial", {"Grass"}},
        {"Park", {"Grass", "Bush", "Flower"}},
        {"Hill", {"Fern"}},
        {"Mountain", {"Fern", "Grass"}},
        {"River", {"Reeds"}},
        {"Lake", {"Water Lily"}},
        {"Forest", {"Moss", "Fern"}},
        {"Wetland", {"Cattail"}}
    };

    // Define area-specific building characteristics
    areaSpecificBuildingFloors = {
        {"Downtown", 10},
        {"Suburban", 3},
        {"Industrial", 5},
        {"Park", 1},
        {"Hill", 2},
        {"Mountain", 2},
        {"River", 1},
        {"Lake", 1},
        {"Forest", 1},
        {"Wetland", 1}
    };

    areaSpecificBuildingCapacities = {
        {"Downtown", 500},
        {"Suburban", 100},
        {"Industrial", 300},
        {"Park", 50},
        {"Hill", 20},
        {"Mountain", 20},
        {"River", 10},
        {"Lake", 10},
        {"Forest", 10},
        {"Wetland", 10}
    };

    areaSpecificBuildingTypes = {
        {"Downtown", {"Office", "Apartment", "Mall"}},
        {"Suburban", {"House", "School", "Supermarket"}},
        {"Industrial", {"Factory", "Warehouse"}},
        {"Park", {"Pavilion", "Restroom"}},
        {"Hill", {"House"}},
        {"Mountain", {"Cabin"}},
        {"River", {"Boat House"}},
        {"Lake", {"Boat House"}},
        {"Forest", {"Cabin", "Ranger Station"}},
        {"Wetland", {"Cabin", "Ranger Station"}}
    };

    areaPopulationDensity = {
        {"Downtown", 5000},
        {"Suburban", 1000},
        {"Industrial", 500},
        {"Park", 200},
        {"Hill", 100},
        {"Mountain", 50},
        {"River", 20},
        {"Lake", 20},
        {"Forest", 10},
        {"Wetland", 10}
    };

    areaSpecificPopulations = {
        {"Downtown", 0.0},
        {"Suburban", 0.0},
        {"Industrial", 0.0},
        {"Park", 0.0},
        {"Hill", 0.0},
        {"Mountain", 0.0},
        {"River", 0.0},
        {"Lake", 0.0},
        {"Forest", 0.0},
        {"Wetland", 0.0}
    };

    // Define terrain constraints
    terrainConstraints = {
        {"Hill", {"House", "Cabin", "Pine", "Fern"}},
        {"Mountain", {"Cabin", "Pine", "Birch", "Fern"}},
        {"Forest", {"Cabin", "Ranger Station", "Fir", "Spruce", "Pine", "Moss", "Fern"}},
        {"Wetland", {"Cabin", "Ranger Station", "Mangrove", "Cattail"}},
        {"River", {"Boat House", "Willow", "Reeds"}},
        {"Lake", {"Boat House", "Cypress", "Water Lily"}}
    };
}

void CityGenerator::generateCity(int iterations) {
    generateTerrain();
    std::string result = lsystem.generate(iterations);

    // For simplicity, let's assume each area type is evenly distributed.
    size_t areaIndex = 0;

    for (char c : result) {
        std::string area = geographicalAreas[areaIndex % geographicalAreas.size()];
        processSymbol(c, area);
        areaIndex++;
    }

    arrangeBuildingsAndFeatures();

    roadNetwork.generateNetwork(50, 100); // Example parameters for the road network

    // Calculate populations
    for (const auto &building : cityMap) {
        areaSpecificPopulations[building.getGeographicalArea()] += building.getCapacity();
    }
}

void CityGenerator::generateTerrain() {
    for (const auto &area : geographicalAreas) {
        if (area == "Hill" || area == "Mountain") {
            int numHills = rand() % 5 + 1;
            for (int i = 0; i < numHills; ++i) {
                double height = rand() % 300 + 50;
                geographicalFeatures.emplace_back("Hill", "Height: " + std::to_string(height) + "m", area);
            }
        } else if (area == "River") {
            int numRivers = rand() % 3 + 1;
            for (int i = 0; i < numRivers; ++i) {
                double width = rand() % 100 + 10;
                geographicalFeatures.emplace_back("River", "Width: " + std::to_string(width) + "m", area);
            }
        } else if (area == "Lake") {
            int numLakes = rand() % 3 + 1;
            for (int i = 0; i < numLakes; ++i) {
                double areaSize = rand() % 5000 + 500;
                geographicalFeatures.emplace_back("Lake", "Area: " + std::to_string(areaSize) + "sqm", area);
            }
        }
    }
}

void CityGenerator::processSymbol(char symbol, const std::string &area) {
    std::string type;
    std::string geographicalDetail;

    switch (symbol) {
        case 'A':
            type = "Road";
            cityMap.emplace_back(type, "Asphalt", area, 1, 0);
            break;
        case 'B':
            type = "Building";
            break;
        case 'C':
            type = "Parking Lot";
            cityMap.emplace_back(type, "Concrete", area, 1, 50);
            break;
        case 'D':
            type = "Government Headquarters";
            cityMap.emplace_back(type, "Concrete", area, areaSpecificBuildingFloors[area], areaSpecificBuildingCapacities[area]);
            break;
        case 'E':
            type = "Power Station";
            cityMap.emplace_back(type, "Steel", area, 2, 30);
            break;
        case 'F':
            type = "Business";
            cityMap.emplace_back(type, "Glass", area, 5, 200);
            break;
        case 'G':
            type = "Park";
            break;
        case 'R':
            type = "River";
            geographicalDetail = "Width: " + std::to_string(rand() % 100 + 1) + "m";
            geographicalFeatures.emplace_back(type, geographicalDetail, area);
            break;
        case 'T':
            type = "Tree";
            geographicalDetail = areaSpecificTrees[area][rand() % areaSpecificTrees[area].size()];
            geographicalFeatures.emplace_back(type, geographicalDetail, area);
            break;
        case 'U':
            type = "Hill";
            geographicalDetail = "Height: " + std::to_string(rand() % 300 + 1) + "m";
            geographicalFeatures.emplace_back(type, geographicalDetail, area);
            break;
        case 'V':
            type = "Mountain";
            geographicalDetail = "Height: " + std::to_string(rand() % 1000 + 1) + "m";
            geographicalFeatures.emplace_back(type, geographicalDetail, area);
            break;
        case 'W':
            type = "Lake";
            geographicalDetail = "Area: " + std::to_string(rand() % 5000 + 1) + "sqm";
            geographicalFeatures.emplace_back(type, geographicalDetail, area);
            break;
        case 'X':
            type = "Plant";
            geographicalDetail = areaSpecificPlants[area][rand() % areaSpecificPlants[area].size()];
            geographicalFeatures.emplace_back(type, geographicalDetail, area);
            break;
        default:
            type = "Unknown";
    }

    // Only add detailed building information if the type is not "Unknown" or a geographical feature
    if (type != "Unknown" && type != "River" && type != "Tree" && type != "Hill" && type != "Mountain" && type != "Lake" && type != "Plant") {
        std::string material = materials[rand() % materials.size()];
        int floors = areaSpecificBuildingFloors[area];
        int capacity = areaSpecificBuildingCapacities[area];
        std::string buildingType = areaSpecificBuildingTypes[area][rand() % areaSpecificBuildingTypes[area].size()];

        // Ensure constraints are met for the specific area
        if (terrainConstraints.find(area) != terrainConstraints.end()) {
            const auto &constraints = terrainConstraints[area];
            if (std::find(constraints.begin(), constraints.end(), buildingType) != constraints.end()) {
                cityMap.emplace_back(buildingType, material, area, floors, capacity);
            }
        } else {
            cityMap.emplace_back(buildingType, material, area, floors, capacity);
        }
    }
}

void CityGenerator::arrangeBuildingsAndFeatures() {
    // Sort cityMap by geographical area for better arrangement
    std::sort(cityMap.begin(), cityMap.end(), [](const Building &a, const Building &b) {
        return a.getGeographicalArea() < b.getGeographicalArea();
    });

    // Sort geographicalFeatures by area for better arrangement
    std::sort(geographicalFeatures.begin(), geographicalFeatures.end(), [](const GeographicalFeature &a, const GeographicalFeature &b) {
        return a.getArea() < b.getArea();
    });
}

void CityGenerator::printCity() const {
    for (const auto &building : cityMap) {
        std::cout << "Type: " << building.getType()
                  << ", Material: " << building.getMaterial()
                  << ", Geographical Area: " << building.getGeographicalArea()
                  << ", Floors: " << building.getFloors()
                  << ", Capacity: " << building.getCapacity() << std::endl;
    }
    for (const auto &feature : geographicalFeatures) {
        std::cout << "Type: " << feature.getType()
                  << ", Details: " << feature.getDetails()
                  << ", Area: " << feature.getArea() << std::endl;
    }

    roadNetwork.printNetwork();

    std::cout << "\nPopulation Distribution:\n";
    for (const auto &area : geographicalAreas) {
        std::cout << area << ": " << areaSpecificPopulations.at(area) << std::endl;
    }
}

void CityGenerator::saveCityToROOT(const std::string &filename) const {
    std::filesystem::path filePath(filename);
    std::filesystem::create_directories(filePath.parent_path());

    TFile file(filename.c_str(), "RECREATE");
    TTree tree("CityTree", "City Layout");

    std::string type;
    std::string material;
    std::string geographicalArea;
    std::string details;
    int floors;
    int capacity;
    double population;
    tree.Branch("Type", &type);
    tree.Branch("Material", &material);
    tree.Branch("GeographicalArea", &geographicalArea);
    tree.Branch("Details", &details);
    tree.Branch("Floors", &floors);
    tree.Branch("Capacity", &capacity);
    tree.Branch("Population", &population);

    for (const auto &building : cityMap) {
        type = building.getType();
        material = building.getMaterial();
        geographicalArea = building.getGeographicalArea();
        details = "";
        floors = building.getFloors();
        capacity = building.getCapacity();
        population = 0;
        tree.Fill();
    }

    for (const auto &feature : geographicalFeatures) {
        type = feature.getType();
        details = feature.getDetails();
        geographicalArea = feature.getArea();
        material = "";
        floors = 0;
        capacity = 0;
        population = 0;
        tree.Fill();
    }

    for (const auto &area : geographicalAreas) {
        type = "Area Population";
        material = "";
        geographicalArea = area;
        details = "";
        floors = 0;
        capacity = 0;
        population = areaSpecificPopulations.at(area);
        tree.Fill();
    }

    tree.Write();
    file.Close();
}
