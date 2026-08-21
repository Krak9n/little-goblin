#include "http_requests.h"

static HashMap* head = NULL;
// Smarter approach from my side would be to not create another struct,
// but to just use pairs with some default integer keys. Will take it into consideration.
static HeaderString* h_s = NULL;

bool isNull(void* value) {
	if (value == NULL) {
		fprintf(stderr, "Failed to allocate memory.\n");
		return false;
	}
	else {
		return true;
	}
}

// New function for me.
// Reference: https://www.ibm.com/docs/en/zos/3.2.0?topic=functions-strrchr-find-last-occurrence-character-in-string
char* parse_last_line_headers(char* headers) {
	char* last_newline = (strrchr(headers, '\n'));
    if (last_newline != NULL) {
        return last_newline + 1;
    } else {
        return headers;
    }
}

void addHeaderString(char* value) {
	HeaderString* temp = malloc(sizeof(HeaderString));
	temp->next = NULL;
	temp->string_v = strdup(value);
	if (!isNull(temp->string_v)) {
		exit(1);
	}

	if (h_s == NULL) {
		h_s = temp;
		return;
	}
	else {
		HeaderString* temp2 = h_s;

		while (temp2->next != NULL) {
			temp2 = temp2->next;
		}
		temp2->next = temp; 
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
	head = newHashMap();
	char* header_fields = strdup(header_fields_parsed);
	if (!isNull(header_fields)) {
		exit(1);
	}

	char* tokenized_fields = strtok(header_fields, "\n");

	while (tokenized_fields) {
		addHeaderString(tokenized_fields);
		if (strstr(tokenized_fields, "Content-Length") != NULL) {
			tokenized_fields = strtok(NULL, "?0");
		} else {
			tokenized_fields = strtok(NULL, "\n");
		}
	}
	printf("Parsed values: \n");
	while (h_s != NULL) {
		printf("%s\n", h_s->string_v);
		h_s = h_s->next;
	}

	while (h_s != NULL) {
		char* field = strtok(h_s->string_v, ":");
		if (field == NULL) {
			break;
		}
		char* status = strtok(NULL, "\0");
		if (status == NULL) {
			break;
		}
		addPair(head, field, status);
		h_s = h_s->next;
	}
}

HttpRequests newHttpRequests(const char *request_string) {
	char* requested = malloc(strlen(request_string));
	requested = strdup(request_string);
	if (!isNull(requested)) {
		printf("Failed to allocated memory for the main string.\n");
		exit(1);
	}
	for (u_int i = 0; i < strlen(requested); ++i) {
		if (requested[i] == '\n' && requested[i+1] == '\n') {
			requested[i + 1] = '|';
		}
	}

	char* request_line = strtok(requested, "\n");
	if (request_line != NULL) {
		printf("Request line: %s\n", request_line);
	}
	char* headers = strtok(NULL, "|");

	HttpRequests request;
	char* method = strtok(request_line, " ");
	if (method != NULL) {
		printf("Method: %s\n", method);
	}

	// Currently not needed.
	for (u_int method_definition = GET; method_definition <= PRI; ++method_definition) {
		if (!strcmp(method, HTTP_METHODS[method_definition])) {
			printf("Used method: %s\n", HTTP_METHODS[method_definition]);
		}
	}

	request.method = *method;
	char* URI = strtok(NULL, " ");
	request.URI = URI;

	// GET / HTTP/1.1
	// I have to separate firstly until the first space. 
	// Then the first slash, and after that after the second slash,
	// since I do not need the HTTP in an HTTP server.
	char* http_version = strtok(NULL, " ");
	http_version = strtok(http_version, "/");
	http_version = strtok(NULL, "/");
	request.http_version = atof(http_version);

	// Have to go over all entries and make pairs.
	parseHeaders(headers);
	request.head = head;
	char* body = parse_last_line_headers(headers);
	request.body = body;
	
	return request;
}
