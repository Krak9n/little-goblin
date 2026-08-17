#pragma once

#include <string.h>
#include "hashmap/hashmap.h"

typedef unsigned int uint;

typedef struct Routes {
	uint length;
	HashMap* routes;
} Routes;

void add_route(char* key, void* value);
void init_routes();
void print_routes();
