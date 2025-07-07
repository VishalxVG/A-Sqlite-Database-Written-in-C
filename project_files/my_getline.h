#ifndef MY_GETLINE_H
#define MY_GETLINE_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/types.h> // for ssize_t on Linux; on Windows may need <BaseTsd.h>

ssize_t my_getline(char **lineptr, size_t *n, FILE *stream);

#endif
