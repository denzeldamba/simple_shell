#include "shell.h"

/* 
 * get_string_length - returns the length of a string
 * @str: the string whose length to check
 *
 * Return: integer length of string
 */
int get_string_length(char *str)
{
    int length = 0;

    if (!str)
        return (0);

    // Loop until the end of the string
    while (*str++)
        length++;

    return (length);
}

/* 
 * compare_strings - performs lexicographic comparison of two strings.
 * @s1: the first string
 * @s2: the second string
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int compare_strings(char *s1, char *s2)
{
    // Loop until the end of either string is reached
    while (*s1 && *s2)
    {
        if (*s1 != *s2)
            return (*s1 - *s2);
        s1++;
        s2++;
    }

    // Check if both strings have reached the null terminator
    if (*s1 == *s2)
        return (0);
    else
        return (*s1 < *s2 ? -1 : 1);
}

/* 
 * string_starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next character of haystack or NULL
 */
char *string_starts_with(const char *haystack, const char *needle)
{
    while (*needle)
    {
        if (*needle++ != *haystack++)
            return (NULL);
    }
    return ((char *)haystack);
}

/* 
 * concatenate_strings - concatenates two strings
 * @destination: the destination buffer
 * @source: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *concatenate_strings(char *destination, char *source)
{
    char *result = destination;

    // Move to the end of the destination string
    while (*destination)
        destination++;

    // Copy characters from the source to the end of the destination
    while (*source)
        *destination++ = *source++;

    // Append the null terminator
    *destination = *source;

    return (result);
}
