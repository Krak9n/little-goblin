cmake_minimum_required(VERSION 3.23)
set(CMAKE_C_STANDARD 99)

project(little-goblin)

file(GLOB_RECURSE SOURCE_FILES src/*.c src/*.h)

set(SOURCES
	src/main.c
	src/server/server.c
	src/http/http.c
	src/hashmap/hashmap.c
)
add_executable(${PROJECT_NAME}
	${SOURCES}
)

target_include_directories(${PROJECT_NAME}
	PRIVATE
		src/
)
