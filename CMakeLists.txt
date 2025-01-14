cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
project(forcesOfNature VERSION 1.0)

include_directories("game" 
                    "libs"
                    )

#link sdl3 libraries
find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)
find_package(SDL3_image REQUIRED)
find_package(SDL3_ttf REQUIRED)

set(SOURCES 
    libs/SDLTools/LTimer.cpp
    game/Game.cpp
    )

add_executable(forcesOfNature.out main.cpp ${SOURCES})
target_link_libraries(forcesOfNature.out PRIVATE SDL3::SDL3 SDL3_image SDL3_ttf)