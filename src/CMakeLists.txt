set(SRC_FILES
        main.cpp
        Game.cpp
        Map.cpp
        Player.cpp
        Textures.cpp
        Tile.cpp
        noiseutils.cpp
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


#copy the needed dll files to the output directory
if (WIN32)
	# copy libnoise.dll (included with this project)
	configure_file("${CMAKE_SOURCE_DIR}/lib/noise/libnoise.dll" "${CMAKE_BINARY_DIR}/bin" COPYONLY)

	# copy SFML dlls
	configure_file("${SFML_INCLUDE_DIR}/../bin/sfml-window-d-2.dll" "${CMAKE_BINARY_DIR}/bin" COPYONLY)
	configure_file("${SFML_INCLUDE_DIR}/../bin/sfml-system-d-2.dll" "${CMAKE_BINARY_DIR}/bin" COPYONLY)

	# copy assets folder to output directory so executable can properly load the assets
	file(COPY "${CMAKE_SOURCE_DIR}/Assets/" DESTINATION "${CMAKE_BINARY_DIR}/bin/Assets")
endif()