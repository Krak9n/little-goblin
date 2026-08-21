#pragma once

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "http_requests/http_requests.h"

#define BUFFER_SIZE 30000

typedef unsigned int u_int;

typedef struct HttpResponse {
	char* status;
	char* body;
	u_int size;
} HttpResponse;

char *read_file(const char* path);
char* mime_type(const char* path);
HttpResponse* newHttpResponse(char* filename, char* status, HttpRequests* http_requests);
