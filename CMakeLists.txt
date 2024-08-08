cmake_minimum_required(VERSION 3.10)

project(ProceduralCityGenerator)

# Specify C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ROOT REQUIRED)
include_directories(${ROOT_INCLUDE_DIRS})

# Ensure the -Zc:__cplusplus flag is used
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Zc:__cplusplus")
include_directories(include)
add_executable(ProceduralCityGenerator
        src/main.cpp
        src/lsystem.cpp
        src/city_generator.cpp
        src/building.cpp
        src/geographical_feature.cpp
        src/road_network.cpp
)

target_link_libraries(ProceduralCityGenerator ${ROOT_LIBRARIES})
