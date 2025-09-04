#include "mime.h"

const char *status_code_serialize(int status_code) {
  if (status_code == 200) {
    return "200 OK";
  }
  if (status_code == 400) {
    return "400 BAD_REQUEST";
  }
  if (status_code == 404) {
    return "404 NOT_FOUND";
  }
  if (status_code == 500) {
    return "500";
  }

  return "";
}

char *getFileType(char *path) {
  if (strstr(path, ".html")) {
      return "text/html";
  }

  if (strstr(path, ".css")) {
      return "text/css";
  }
  
  if (strstr(path, ".js")) {
      return "application/javascript";
  }
  
  if (strstr(path, ".jpg") || strstr(path, ".jpeg")){ 
      return "image/jpeg";
  }
  
  if (strstr(path, ".png")) {
      return "image/png";
  }
  
  if (strstr(path, ".mp4")) {
      return "video/mp4";
  }
  
  return NULL; // Return NULL if no match is found
}
