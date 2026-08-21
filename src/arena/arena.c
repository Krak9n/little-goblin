#include "arena.h"

// Needs a proper rewrite. Gods my head hurts.
void* allocate(Arena* arena, size_t size, size_t alignment) {
}

u_int deallocate(Arena* arena) {
	free(arena->buffer);
}

Arena* newArena() {
	Arena* arena;
	arena->buffer = 0;
	arena->size = 0;
	arena->offset = 0;
	return arena;
}
