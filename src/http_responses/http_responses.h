#pragma once

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "http_requests/http_requests.h"

#define BUFFER_SIZE 30000

int page(HttpRequests* http_requests, int socket, char* pass_buffer, char* path);
char *read_file(const char* path);
const char* mime_type(const char* path);

static const char *status_success = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";

