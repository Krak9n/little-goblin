#include "vector.h"

// Need to be rewritten later.
// Correct reallocation of a void array.
void addElement(Vector* vector, void* element) {
	if (vector->held_data == NULL) {
		// Just an empty vector dude.
		vector->held_data = (void* )malloc(sizeof(element));
		vector->size = 1; 
	}
	else if (vector->size >= vector->allocated_capacity) {
		vector->allocated_capacity *= 2;
		vector->held_data = (void *)realloc(vector->held_data, vector->allocated_capacity * sizeof(void *));
	}

	vector->held_data[vector->size] = element;
	vector->size += 1;
}

void removeElement(Vector* vector, u_int position) {
	if (position >= vector->size) {
		printf("Called index is greater than the vector's size.");
		exit(1);
	}
	vector->held_data[position] = NULL;
	vector->size -= 1;
	// could use size though
	for (size_t i = 0; i < (sizeof(vector->held_data) / sizeof(vector->held_data[0])); ++i) {
		memmove(&vector->held_data[i - 1], &vector->held_data, ((vector->size - i) * sizeof(*vector->held_data)));
		memset(&vector->held_data[vector->size - i], 0, i * sizeof(*vector->held_data));
	}
}

void* getElement(Vector* vector, u_int position) {
	if (position >= vector->size) {
		printf("Called index is greater than the vector's size. Please change the index before calling a function.");
		exit(1);
	}
	return vector->held_data[position];
}

Vector* newVector() {
	Vector* vector = (Vector* )malloc(sizeof(Vector));
	vector->held_data = NULL;
	vector->size = 0;
	vector->allocated_capacity = 0;
	return vector;
}

