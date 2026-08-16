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
	char* URI;
	double httpVersion;
	char* body;
	HashMap* headers_head;
} HttpRequests;

HttpRequests newHttpRequests(const char* request_string);
void parseHeaders(const char* header_fields_parsed);

char* parseLastHeadersLine(const char *headers);

typedef struct HeaderString {
  char* string_v;
  struct HeaderString *next;
} HeaderString;

void addHeaderString(HeaderString* h_s, const char* value);
void clearHeaderString(HeaderString* h_s);
