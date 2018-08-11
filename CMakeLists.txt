cmake_minimum_required(VERSION 3.6)

project(Tseitr)
set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(Tseitr main.cpp)
target_link_libraries(Tseitr ${SDL2_LIBRARIES})