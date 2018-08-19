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

# find_library(NOISE_LIB libnoise PATHS ${PROJECT_SOURCE_DIR}/lib/noise)

add_library(libnoise STATIC IMPORTED)

if (WIN32)
	set_target_properties(libnoise PROPERTIES
		IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/lib/noise/libnoise.lib"
		INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/include/noise"
	)
endif()

add_executable(${EXECUTABLE_NAME} ${SRC_FILES})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2.4 REQUIRED audio network graphics window system)
if(SFML_FOUND)
    # include_directories(${SFML_INCLUDE_DIR})
	include_directories(${PROJECT_SOURCE_DIR}/include ${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} libnoise)
endif()
