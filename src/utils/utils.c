#include "utils.h"

char *getFile(char *path) {
 
  char *whole = (char*)malloc(154); // we ll see if it fails
  char *type = (char*)malloc(130);
  FILE *file = fopen(path + 1, "r"); // skips the leading "/"
  if (NULL == file) {
    file = fopen("../src/web/404.html", "r");

    if (NULL == file) {
      sprintf(whole,   
          "HTTP/1.1 404 Not Found\r\n"
          "Content-Type: text/plain\r\n"
          "Content-Length: 13\r\n"
          "\r\n"
          "404 Not Found"
      );

      return whole;
    }
  }

  type = getFileType(path);
  if (NULL == type) { 
    type = "application/octet-stream";
  } 

  sprintf(
      whole,  
      "HTTP/1.1 200 OK\r\n"
      "Content-Type: %s\r\n",
      type
  );

  fclose(file);
  return whole;

}

char* readfile(FILE *f) {
  
  if (f == NULL || fseek(f, 0, SEEK_END)) {
    return NULL;
  }

  long length = ftell(f);
  rewind(f);
 
  if (length == -1 || (unsigned long) length >= SIZE_MAX) {
    return NULL;
  }

  // converting from long to size_t
  size_t ulength = (size_t) length;
  char *buffer = malloc(ulength + 1);
  
  if (buffer == NULL || fread(buffer, 1, ulength, f) != ulength) {
    free(buffer);
    return NULL;
  }
  buffer[ulength] = '\0'; // now buffer points to a string
  
  return buffer;
}



char *concat(char *help, char *hope) {
  strcat(help, hope);
  return help;
}

void intToString(int num, char str[]) {
  int i = 0, isNegative = 0;

  if (num == 0) {
    str[i++] = '0';
    str[i] = '\0';
    return;
  }

  if (num < 0) {
    isNegative = 1;
    num = -num;
  }

  while (num != 0) {
    int digit = num % 10;
    str[i++] = digit + '0';
    num = num / 10;
  }

  if (isNegative)
    str[i++] = '-';

  str[i] = '\0';

  int start = 0, end = i - 1;
  while (start < end) {
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    start++;
    end--;
  }
}


