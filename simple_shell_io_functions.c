#include "shell.h"

/**
 * _print_to_stderr - Prints a string to stderr.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void _print_to_stderr(char *str)
{
    if (str)
        write(2, str, _string_length(str));
}

/**
 * _print_character_to_stderr - Writes a character to stderr.
 * @c: The character to print.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _print_character_to_stderr(char c)
{
    return write(2, &c, 1);
}

/**
 * _write_character_to_file_descriptor - Writes a character to the given file descriptor.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _write_character_to_file_descriptor(char c, int fd)
{
    return write(fd, &c, 1);
}

/**
 * _print_string_to_file_descriptor - Prints a string to the specified file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters written.
 */
int _print_string_to_file_descriptor(char *str, int fd)
{
    if (!str)
        return 0;

    int count = 0;
    while (*str)
    {
        if (_write_character_to_file_descriptor(*str, fd) == -1)
            return -1;
        str++;
        count++;
    }
    return count;
}

