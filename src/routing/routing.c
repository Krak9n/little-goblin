#include "routing.h"

Routes* rs = NULL;

void add_route(char* key, void* value) {
	HashMap* temp = newHashMap();
	printf("1\n");
	printf("%s\n", key);
	(*temp->pairs)->key = key;

	printf("2\n");
	(*temp->pairs)->value = value;

	printf("3\n");
	(*temp->pairs)->next = NULL;

	printf("4\n");
	if (rs->routes != NULL) {

		printf("5\n");
		Routes* temp2 = rs;

		printf("6\n");
		printf("entered\n");
		while ((*temp2->routes->pairs)->next != NULL) {

			printf("entered2\n");
			*temp2->routes->pairs = (*temp2->routes->pairs)->next;
			printf("entered3\n");
		}

		printf("7\n");
		(*temp2->routes->pairs)->next = *temp->pairs;

		printf("8\n");
	}
	else {

		printf("9\n");
		rs->routes = temp;

	printf("10\n");
	}
}
/*
void init_routes() {
	rs->routes = newHashMap();
	printf("inits\n");
	}*/

void print_routes() {
	Routes* temp_rs = rs;
	while (temp_rs->routes->pairs != NULL) {
		printf("Routes: %s -> %s",
			   (*temp_rs->routes->pairs)->key,
			   (getValue(temp_rs->routes, (*temp_rs->routes->pairs)->key))
			   );
		*temp_rs->routes->pairs = (*temp_rs->routes->pairs)->next;
	}
}
