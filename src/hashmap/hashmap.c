#include "hashmap.h"

HashMap* newHashMap() {
	HashMap* this = malloc(sizeof(this));
	this->capacity = HASHMAP_SIZE_DEFAULT;
	this->length = 0;
	// Initializes allocated memory to zero.
	this->pairs = calloc(this->capacity, sizeof(Pair*));
	return this;
}

// Definition here: https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
static uint hashcode(HashMap* this, char* key) {
	l_uint code = FNV_OFFSET_BASIS;
	for (const char* val = key; *val; ++val) {
		code ^= *val;
		code *= FNV_PRIME;
	}
	return code;
}

void addPair(HashMap* this, char* key, void* value) {
	if (value == NULL) {
		return;
	}

	uint index = hashcode(this, key);
	Pair* the_pair = malloc(sizeof(*the_pair));

	for (the_pair = this->pairs[index]; the_pair; the_pair = the_pair->next) {
		if (!strcmp(the_pair->key, key)) {
			the_pair->value = value;
			return;
		}
	}

	the_pair->key = key;
	the_pair->value = value;
	the_pair->next = this->pairs[index];
	this->pairs[index] = the_pair;
	++this->length;
}

void* getValue(HashMap* this, char* key) {
	Pair* the_pair;
	for (the_pair = this->pairs[hashcode(this, key)]; the_pair; the_pair = the_pair->next) {
		if (!strcmp(the_pair->key, key)) {
			return the_pair->value;
		}
	}
	sprintf("%s was not found in the HashMap.", key);
	exit(1);
}

void destroyHashMap(HashMap* this) {
	for (uint i = 0; i < this->capacity; ++i) {
		free(this->pairs[i]->key);
	}
	free(this->pairs);
	free(this);
}

void getWholeHashMap(HashMap* this) {
	while (this->pairs != NULL) {
		printf("entered pairs\n");
		printf("%s: %s\n", ((*this->pairs)->key), (getValue(this, (*this->pairs)->key)));
		(*this->pairs) = (*this->pairs)->next;
	}
}

size_t size(HashMap* this) {
	return this->length;
}
