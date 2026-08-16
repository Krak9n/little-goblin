#include "http_requests.h"

static HashMap* headers = NULL;

// More here: https://www.ibm.com/docs/en/zos/3.2.0?topic=functions-strrchr-find-last-occurrence-character-in-string
char* parseLastHeadersLine(const char *headers) {
	return (strrchr(headers, '\n'));
}

void addHeaderString(HeaderString* h_s, const char* value) {
	HeaderString* header_string = malloc(sizeof(*header_string));
	header_string->next = NULL;
	header_string->string_v = strndup(value, strlen(value));

	if (h_s == NULL) {
		h_s = header_string;
		return;
	}
	else {
		clearHeaderString(header_string);
		header_string = h_s;
		while (header_string->next != NULL) {
			header_string = header_string->next;
		}
		header_string->next = h_s; 
	}
}

void clearHeaderString(HeaderString* h_s) {
	HeaderString* temp;
	while (h_s != NULL) {
		temp = h_s->next;
		free(h_s);
		h_s = temp; // apparently needs malloc?
	}
	free(temp);
}

void parseHeaders(const char* header_fields_parsed) {
	headers = newHashMap();
	HeaderString* header_string;
	char header_fields[strlen(header_fields_parsed)];

	char *single_fields = strtok(single_fields, (void *)'\n');
	for (;;single_fields) {
		addHeaderString(header_string, single_fields);
	}

	while (header_string != NULL) {
		char* field = strtok(header_string->string_v, (void *)':');
		if (field == NULL) {
			break;
		}
		char* status = strtok(NULL, (void *)'\0');
		if (status == NULL) {
			break;
		}
		addPair(headers, field, status);
		header_string = header_string->next;
	}
}

HttpRequests newHttpRequests(const char *request_string) {
	char* requested = malloc(strlen(request_string));
	for (uint i = 0; i < (strlen(requested) - 2); ++i) {
		if ((requested[i] && requested[i+1]) == '\n') {
			requested[i + 1] = '|';
		}
	}

	char* request_line = strtok(requested, (void *)'\n');
	char* header_fields = strtok(NULL, (void *)'|');

	HttpRequests request;
	char* method = strtok(request_line, " ");
	for (uint method_definition = GET; method_definition <= PRI; ++method_definition) {
		if (strcmp(method, HTTP_METHODS[method_definition])) {
			request.method = method_definition;
		}
	}

	char* URI = strtok(NULL, " ");
	request.method = *method;
	request.URI = URI;

	// GET / HTTP/1.1
	// I have to separate firstly until the first space. 
	// Then the first slash, and after that after the second slash,
	// since I do not need the HTTP in an HTTP server.
	char* http_version = strtok(NULL, " ");
	http_version = strtok(http_version, (void *)'/');
	http_version = strtok(NULL, (void *)'/');
	request.httpVersion = atof(http_version);

	// Have to go over all entries and make pairs.
	parseHeaders(header_fields);
	request.headers_head = headers;
	getWholeHashMap(headers);

	char* response_body = parseLastHeadersLine(header_fields);
	request.body = response_body;
	
	return request;
}
