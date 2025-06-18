#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "my_getline.h"

// Creates a struct to hold the state of the user input
typedef struct
{
    char *buffer;         // pointer to actual user stirng
    size_t buffer_length; // size of buffer
    ssize_t input_length; // length of input string
} InputBuffer;

// Allocates a new InputBuffer in heap memory(so it is persistant even after function call) , and initializes its fields to zero/null and return it.
InputBuffer *new_input_buffer()
{
    InputBuffer *input_buffer = (InputBuffer *)malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;

    return input_buffer;
}
// simply prints "db >" on the terminal
void print_prompt() { printf("db > "); }

// reads entire line of text from input stdin into a dynamically allocated buffer
// ssize_t getline(char **lineptr, size_t *n, FILE *stream);
void read_input(InputBuffer *input_buffer)
{
    ssize_t bytes_read =
        my_getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

    if (bytes_read <= 0)
    {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    // Ignore trailing newline
    input_buffer->input_length = bytes_read - 1;
    input_buffer->buffer[bytes_read - 1] = 0;
}

void close_input_buffer(InputBuffer *input_buffer)
{
    free(input_buffer->buffer);
    free(input_buffer);
}

int main(int argc, char *argv[])
{
    InputBuffer *input_buffer = new_input_buffer();
    while (true)
    {
        print_prompt();
        read_input(input_buffer);

        if (strcmp(input_buffer->buffer, ".exit") == 0)
        {
            close_input_buffer(input_buffer);
            exit(EXIT_SUCCESS);
        }
        else
        {
            printf("Unrecofnized commad '%s' .\n", input_buffer->buffer);
        }
    }
}
