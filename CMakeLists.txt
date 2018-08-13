cmake_minimum_required(VERSION 3.6)

project(Tseitr)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})

set(SOURCE_FILES main.cpp
        Game.cpp Game.hpp
        Screen.hpp
        StartScreen.cpp StartScreen.hpp
        GameScreen.cpp GameScreen.hpp
        Level.cpp Level.hpp
        Tetromino.cpp Tetromino.hpp
        )

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/font.ttf" "${CMAKE_BINARY_DIR}/font.ttf" COPYONLY)

add_executable(Tseitr ${SOURCE_FILES})
target_link_libraries(Tseitr ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARIES})