cmake_minimum_required(VERSION 3.22.1)
project(AstronautCat VERSION 1.0.0)

add_library(lib ./includes/Head.h ./lib/Func.c)
add_executable(Solution ./src/main.c)
