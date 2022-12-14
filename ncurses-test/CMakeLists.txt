cmake_minimum_required(VERSION 3.22.1)
project(AstronautCat VERSION 1.0.0)


add_library(lib ./includes/HeaderGraphic.h ./lib/GraphicFunctions.cpp ./lib/Func.cpp)
link_libraries(lib -lncurses)
add_executable(Astronaut ./src/main.cpp)
