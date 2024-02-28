#include "shell.h"

/* Copy a string */
char *copy_string(char *destination, char *source)
{
    int i = 0;

    if (destination == source || source == NULL)
        return destination;

    while (source[i])
    {
        destination[i] = source[i];
        i++;
    }

    destination[i] = '\0';

    return destination;
}

/* Duplicate a string */
char *duplicate_string(const char *str)
{
    int length = 0;
    char *result;

    if (str == NULL)
        return NULL;

    while (*str++)
        length++;

    result = malloc(sizeof(char) * (length + 1));

    if (!result)
        return NULL;

    for (length++; length--;)
        result[length] = *--str;

    return result;
}

/* Print a string */
void print_string(char *str)
{
    int i = 0;

    if (!str)
        return;

    while (str[i] != '\0')
    {
        write_character(str[i]);
        i++;
    }
}

/* Write a character to stdout */
int write_character(char c)
{
    static int count = 0;
    static char buffer[WRITE_BUFFER_SIZE];

    if (c == BUFFER_FLUSH || count >= WRITE_BUFFER_SIZE)
    {
        write(1, buffer, count);
        count = 0;
    }

    if (c != BUFFER_FLUSH)
        buffer[count++] = c;

    return 1;
}
