#include "shell.h"

/**
 * is_interactive - checks if the shell is running interactively
 * @info: the shell information structure
 *
 * Return: 1 if the shell is interactive, 0 otherwise
 */
int is_interactive(info_t *info)
{
    return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delimiter - checks if a character is a delimiter
 * @c: the character to check
 * @delimiters: the string of delimiters
 *
 * Return: 1 if the character is a delimiter, 0 otherwise
 */
int is_delimiter(char c, const char *delimiters)
{
    while (*delimiters)
    {
        if (*delimiters == c)
            return 1;
        delimiters++;
    }
    return 0;
}

/**
 * is_alpha - checks if a character is an alphabetic character
 * @c: the character to check
 *
 * Return: 1 if the character is an alphabetic character, 0 otherwise
 */
int is_alpha(int c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * string_to_int - converts a string to an integer
 * @s: the string to convert
 *
 * Return: the integer value of the string, or 0 if the string is invalid
 */
int string_to_int(char *s)
{
    int sign = 1, flag = 0, output = 0;

    for (int i = 0; s[i] != '\0' && flag != 2; i++)
    {
        if (s[i] == '-')
            sign *= -1;

        if (s[i] >= '0' && s[i] <= '9')
        {
            flag = 1;
            output = output * 10 + (s[i] - '0');
        }
        else if (flag == 1)
            flag = 2;
    }

    return (sign * output);
}