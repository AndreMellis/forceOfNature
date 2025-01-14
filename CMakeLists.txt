cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
project(forcesOfNature VERSION 1.0)

include_directories("game" 
                    "game/objects"
                    "game/choiceSystem"
                    "game/riskSystem"
                    )

add_subdirectory(libs/customCLib) 

#link sdl3 libraries
find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)
find_package(SDL3_image REQUIRED)
find_package(SDL3_ttf REQUIRED)

set(SOURCES 
    game/Game.cpp
    game/objects/Radar.cpp
    game/riskSystem/RiskHandler.cpp
    )

add_executable(forcesOfNature.out main.cpp ${SOURCES})
target_link_libraries(forcesOfNature.out PRIVATE SDL3::SDL3 SDL3_image SDL3_ttf customCLib )

### ASSET MANAGEMENT ###
file( COPY assets DESTINATION ${CMAKE_BINARY_DIR} )