cmake_minimum_required(VERSION 3.23)
set(CMAKE_C_STANDARD 99)

project(little-goblin)

file(GLOB_RECURSE SOURCE_FILES src/*.c src/*.h)

set(SOURCES
	src/main.c
	src/server/server.c
	src/hashmap/hashmap.c
	src/http_requests/http_requests.c
	src/http_responses/http_responses.c
	src/routing/routing.c
	src/vector/vector.c
	src/arena/arena.c
)
add_executable(${PROJECT_NAME}
	${SOURCES}
)

target_include_directories(${PROJECT_NAME}
	PRIVATE
		src/
)
