#include "city_generator.h"
#include <cstdlib>
#include <ctime>

int main() {
    srand(static_cast<unsigned int>(time(nullptr))); // Seed the random number generator

    CityGenerator generator;
    generator.generateCity(5);
    generator.printCity();
    generator.saveCityToROOT("data/city.root");
    return 0;
}
