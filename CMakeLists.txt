cmake_minimum_required(VERSION 3.23)
set(CMAKE_C_STANDARD 99)

project(little-goblin)

file(GLOB_RECURSE SOURCE_FILES src/*.c src/*.h)

set(SOURCES
	src/main.c
	src/server/server.c
)
add_executable(${PROJECT_NAME}
	${SOURCES}
)
