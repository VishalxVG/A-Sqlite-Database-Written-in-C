#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>

/**
 * my_getline() – read an entire line from `stream`, allocate or grow *lineptr as needed.
 *
 * @param lineptr     pointer to your buffer pointer (can be NULL initially)
 * @param n           pointer to your buffer size (can be 0 initially)
 * @param stream      input stream (e.g. stdin)
 * @return            number of characters read (including the '\n'), or -1 on EOF/error
 *
 * Usage:
 *   char *line = NULL;
 *   size_t len = 0;
 *   ssize_t r = my_getline(&line, &len, stdin);
 *   if (r > 0) {
 *     // line contains the input (with trailing '\n'), len is its capacity
 *   }
 *   free(line);
 */
ssize_t my_getline(char **lineptr, size_t *n, FILE *stream)
{
    if (lineptr == NULL || n == NULL || stream == NULL)
    {
        errno = EINVAL;
        return -1;
    }

    size_t pos = 0;
    int c;

    /* If buffer is NULL or size is 0, allocate an initial chunk */
    if (*lineptr == NULL || *n == 0)
    {
        *n = 128;
        *lineptr = malloc(*n);
        if (*lineptr == NULL)
        {
            return -1;
        }
    }

    while (true)
    {
        c = fgetc(stream);
        if (c == EOF)
        {
            if (pos == 0)
            {
                return -1; // no data read, propagate EOF
            }
            break; // some data read; break and return it
        }

        /* Store character */
        (*lineptr)[pos++] = (char)c;

        /* If buffer too small, grow it */
        if (pos + 1 >= *n)
        {
            size_t new_size = *n * 2;
            char *new_ptr = realloc(*lineptr, new_size);
            if (new_ptr == NULL)
            {
                return -1; // realloc failed
            }
            *lineptr = new_ptr;
            *n = new_size;
        }

        /* Stop on newline and include it */
        if (c == '\n')
        {
            break;
        }
    }

    /* Null-terminate and return length */
    (*lineptr)[pos] = '\0';
    return (ssize_t)pos;
}
