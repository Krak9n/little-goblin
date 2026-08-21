#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int u_int;

typedef struct Vector {
	void** held_data;
	u_int size;
	u_int allocated_capacity;
} Vector;

Vector* newVector();
void addElement(Vector* vector, void* element);
void removeElement(Vector* vector, u_int position);
void* getElement(Vector* vector, u_int position);
