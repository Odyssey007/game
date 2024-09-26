cmake_minimum_required(VERSION 3.20)
project(play LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(
    header
    header/battle
    header/battle/player
    header/battle/player/abilities
    header/battle/enemies
    header/battle/enemies/goblinBoss
    header/battle/obstacles
    header/game
    header/kingdom
    header/kingdom/buildings
    header/kingdom/buildings/dynamic
    header/kingdom/buildings/static
    header/kingdom/menu
)

# Gather all source files
file(GLOB SOURCES 
    "source/*.cpp"
    "source/battle/*.cpp"
    "source/battle/player/*.cpp"
    "source/battle/player/abilities/*.cpp"
    "source/battle/enemies/*.cpp"
    "source/battle/enemies/goblinBoss/*.cpp"
    "source/battle/obstacles/*.cpp"
    "source/game/*.cpp"
    "source/kingdom/*.cpp"
    "source/kingdom/buildings/*.cpp"
    "source/kingdom/buildings/dynamic/*.cpp"
    "source/kingdom/buildings/static/*.cpp"
    "source/kingdom/menu/*.cpp"
    )

find_package(SFML 2.5.1 COMPONENTS graphics window system REQUIRED)

add_executable(play ${SOURCES})

set_target_properties(play PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/.."
)

message("Running debug script")
set(CMAKE_BUILD_TYPE Debug)

target_link_libraries(play sfml-graphics sfml-window sfml-system)

target_compile_options(play PRIVATE -g -Wall)