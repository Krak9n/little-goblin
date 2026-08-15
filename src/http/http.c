#include "http.h"

HttpRequests newHttpsRequests(const char *request_string) {
	char* requested = malloc(strlen(request_string));
	for (uint i = 0; i < (strlen(requested) - 2); ++i) {
		if ((requested[i] && requested[i+1]) == '\n') {
			requested[i+1] = '|';
		}
	}

	char* request_line = strtok(requested, (void *)'\n');
	char* header_fields = strtok(NULL, (void *)'|');
	char* respopnse_body = strtok(NULL, (void *)'|');

	HttpRequests request;
	char* method = strtok(request_line, (void *)' ');
	for (uint method_definition = GET; method_definition <= PRI; ++method_definition) {
		if (strcmp(method, HTTP_METHODS[method_definition])) {
			request.method = method_definition;
		}
	}

	char* URI = strtok(NULL, (void *)' ');
	request.URI = URI;

	// GET / HTTP/1.1
	// I have to separate firstly until the first space. 
	// Then the first slash, and after that after the second slash,
	// since I do not need the HTTP in an HTTP server.
	char* http_version = strtok(NULL, (void *)' ');
	http_version = strtok(http_version, (void *)'/');
	http_version = strtok(NULL, (void *)'/');
	request.httpVersion = atof(http_version);

	// Have to go over all entries and make pairs.
	
	return request;
}
