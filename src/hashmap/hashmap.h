#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define HASHMAP_SIZE_MIN       32
#define HASHMAP_SIZE_DEFAULT   128  
#define FNV_OFFSET_BASIS       14695981039346656037UL
#define FNV_PRIME              1099511628211UL

typedef unsigned int uint;
typedef long unsigned int l_uint;

typedef struct Pair {
	char* key;
	void* value;
	struct Pair* next;
} Pair;

typedef struct HashMap {
	Pair** pairs;
	uint capacity; // length of list
	uint length;   // number of elements inside
} HashMap;

HashMap* newHashMap();
static uint hashcode(HashMap* this, char* key);
void addPair(HashMap* this, char* key, void* value);
void* getValue(HashMap* this, char* key);
void destroyHashMap(HashMap *this);
size_t size(HashMap* this);
void getWholeHashMap(HashMap* this);
