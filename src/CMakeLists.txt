set(SRC_FILES
        main.cpp
        Game.cpp Game.hpp
        Map.cpp Map.hpp
        Player.cpp Player.hpp
        Textures.cpp Textures.hpp
        Tile.cpp Tile.hpp
        noiseutils.cpp noiseutils.h
        )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(EXECUTABLE_NAME Warlock)

add_executable(${EXECUTABLE_NAME} ${SRC_FILES})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML REQUIRED audio network graphics window system)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} noise)
endif()
