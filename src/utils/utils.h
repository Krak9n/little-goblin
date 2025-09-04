#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../mime/mime.h"

char *getFile(char *path);
char *readfile(FILE *f);
char *concat(char *help, char *hope);
void intToString(int num, char str[]);

#endif
