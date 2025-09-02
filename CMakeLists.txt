cmake_minimum_required(VERSION 3.13)

# dir indication
project(little-goblin)

# passing sorce
file(GLOB_RECURSE SOURCE_FILES src/*.c src/*.h)

set(CMAKE_C_STANDARD 99) 
# here u have to figure out
# how to setup one for assembly

# binaries
add_executable(little-goblin ${SOURCE_FILES})
