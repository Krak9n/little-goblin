cmake_minimum_required(VERSION 3.13)
project(little-goblin)

file(GLOB_RECURSE SOURCE_FILES src/*.c src/*.h)

set(CMAKE_C_STANDARD 99) 
add_executable(little-goblin ${SOURCE_FILES})
