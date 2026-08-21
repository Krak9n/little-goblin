#pragma once

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hashmap/hashmap.h"

typedef unsigned int u_int;

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
	u_int method;
	char* URI;
	double http_version;
	char* body;
	HashMap* head;
} HttpRequests;

HttpRequests newHttpRequests(const char* request_string);
void parseHeaders(const char* header_fields_parsed);

char* parse_last_line_headers(char *headers);

typedef struct HeaderString {
  char* string_v;
  struct HeaderString *next;
} HeaderString;

void addHeaderString(char* value);
void clearHeaderString(HeaderString* h_s);
bool isNull(void* value);
