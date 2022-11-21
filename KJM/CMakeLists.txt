cmake_minimum_required(VERSION 3.22.1)
project(AstronautCat VERSION 1.0.0)

add_library(lib Head.h Func.c)
add_executable(Solution main.c)
