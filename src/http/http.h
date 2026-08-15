#pragma once

#include <string.h>
#include <stdlib.h>
#include "hashmap/hashmap.h"

typedef unsigned int uint;

enum HttpMethods {
	GET,
	HEAD,
	POST,
	PUT,
	DELETE,
	CONNECT,
	OPTIONS,
	TRACE,
	PATCH,
	QUERY, // Proposed in June 2026
	PRI,
};

static const char *HTTP_METHODS[] = {
    "GET", "HEAD", "POST", "PUT", "DELETE", "CONNECT",
	"OPTIONS", "TRACE", "PATCH", "QUERY", "PRI",
};

typedef struct HttpRequests {
	uint method;
	char *URI;
	double httpVersion;
} HttpRequests;

HttpRequests newHttpRequests(const char* request_string);
