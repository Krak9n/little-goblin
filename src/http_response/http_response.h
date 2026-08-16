#pragma once

#include <string.h>

typedef unsigned int uint;

typedef struct HTTP_RESPONSE {
	char* status;
	char* body;
	uint size;
} HTTP_RESPONSE;

HTTP_RESPONSE newHttpResponse(const char* status);
