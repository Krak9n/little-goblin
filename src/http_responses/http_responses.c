#include "http_responses.h"

// So basically I could just create some sort of linked list and just check
// it for having this particular file extensions that is present in Content-Type?
const char* mime_type(const char* path) {
	char* extension = strrchr(path, '.');
	if (extension == NULL) {
		printf("No file extension detected!");
		return "";
	}

	if (strcmp(extension, "json")) return "application/json";
	else if (strcmp(extension, "pdf")) return "application/pdf";
	else if (strcmp(extension, "json")) return "application/json";
	else if (strcmp(extension, "xml")) return "application/xml";
	else if (strcmp(extension, "zip")) return "application/zip";
	else if (strcmp(extension, "mp3")) return "audio/mpeg";
	else if (strcmp(extension, "ogg")) return "audio/json";
	else if (strcmp(extension, "woff")) return "font/woff";
	else if (strcmp(extension, "woff2")) return "font/woff2";
	else if (strcmp(extension, "jpeg") || strcmp(extension, "jpg")) return "image/jpeg";
	else if (strcmp(extension, "png")) return "image/png";
	else if (strcmp(extension, "svg")) return "image/svg+xml";
	else if (strcmp(extension, "webp")) return "image/webp";
	else if (strcmp(extension, "css")) return "text/css";
	else if (strcmp(extension, "html") || strcmp(extension, "htm")) return "text/html";
	else if (strcmp(extension, "txt")) return "text/plain";
	else if (strcmp(extension, "mp4")) return "video/mp4";
	else if (strcmp(extension, "webm")) return "video/webm";
	else return "application/octet-stream";
}


char *read_file(const char* path) {
	char *buffer;
	long contents_length;

	FILE *file = fopen(path, "rt");
	if (file) {
		fseek(file, 0, SEEK_END);
		contents_length = ftell(file);
		fseek(file, 0, SEEK_SET);
		buffer = malloc(contents_length);

		if (buffer) {
			fread(buffer, 1, contents_length, file);
		}
		fclose(file);
	}
	if (*buffer) {
		printf("File has been read!\n");
	}

	return buffer;
}


int page(HttpRequests* http_requests, int socket, char* pass_buffer, char* path) {
	char *buffer = malloc(BUFFER_SIZE);
	char *greeter = read_file(path);
	strcpy(buffer, status_success);
	strcat(buffer, greeter);
	printf("\n%s\n", buffer);

	write(socket, buffer, strlen(buffer));
	return socket;
}

