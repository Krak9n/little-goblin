#include "http_responses.h"

// So basically I could just create some sort of linked list and just check
// it for having this particular file extensions that is present in Content-Type?
char* mime_type(const char* path) {
	char* extension = strrchr(path, '.') + 1;
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

HttpResponse* newHttpResponse(char* filename, char* status, HttpRequests* http_requests) {
	HttpResponse* response;
	printf("1\n");
	u_int response_length = {0};

	printf("2\n");
	char* hold_response;

	printf("3\n");
	char* response_line = ("%sContent-Type:%s\r\n\r\n", status, mime_type(filename));
	printf("r: %s\n", response_line);
	printf("after response line\n");
	memcpy(
		   hold_response,
		   response_line,
		   sizeof(response_line) * sizeof(char));

	printf("4\n");
	printf("response after memcpy: %s\n", hold_response);
	char* file_buffer = read_file(filename);
	printf("%s\n", file_buffer);

	printf("5\n");

	memcpy(
		   hold_response + strlen(hold_response),
		   file_buffer,
		   strlen(file_buffer));

	printf("6\n");
	response_length += strlen(hold_response);
	
	printf("7\n");
	response->body = hold_response;

	printf("8\n");
	response->size = response_length;

	printf("9\n");
	response->status = status;

	printf("10\n");
	
	printf("== Response ==\n%s\n", response->body);
	// arena guys
	free(hold_response);
	return response;
}
