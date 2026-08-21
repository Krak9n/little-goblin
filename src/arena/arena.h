#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef unsigned int u_int;

typedef struct Arena {
	// In my case buffer is just an allocated space, right?
	u_int* buffer;
	size_t size;
	size_t offset;
} Arena;

Arena* newArena();
void* allocate(Arena* arena, size_t size, size_t alignment);
u_int deallocate(Arena* arena);
