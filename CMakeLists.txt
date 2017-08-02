cmake_minimum_required(VERSION 3.6)
project(Warlock)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(SOURCE_FILES src/main.cpp src/Player.cpp src/Player.h src/Game.cpp src/Game.h src/Textures.h src/Textures.cpp src/Map.cpp src/Map.h src/Tile.cpp src/Tile.h)

# Define sources and executable
set(EXECUTABLE_NAME "WarlockRPG")
add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})


# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML REQUIRED audio network graphics window system)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()
