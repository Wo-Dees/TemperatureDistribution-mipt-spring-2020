cmake_minimum_required(VERSION 3.14)
project(Temperature_distribution)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp CSRmatrix.cpp CSRmatrix.h Solvers.h special_number.cpp special_number.h GUI.cpp GUI.h
        animation.cpp
        animation.h
        menu.cpp
        menu.h
        Window.cpp
        Window.h)

add_executable(Temperature_distribution ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(Temperature_distribution sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
