#include "shell.h"

/**
 * _strncpy - copies a string
 * @destination: the destination string to be copied to
 * @source: the source string
 * @num_characters: the amount of characters to be copied
 * Return: the concatenated string
 */
char *_strncpy(char *destination, char *source, int num_characters)
{
	int index_i, index_j;
	char *original_destination = destination;

	index_i = 0;
	while (source[index_i] != '\0' && index_i < num_characters - 1)
	{
		destination[index_i] = source[index_i];
		index_i++;
	}
	if (index_i < num_characters)
	{
		index_j = index_i;
		while (index_j < num_characters)
		{
			destination[index_j] = '\0';
			index_j++;
		}
	}
	return (original_destination);
}

/**
 * _strncat - concatenates two strings
 * @destination: the first string
 * @source: the second string
 * @num_characters: the amount of bytes to be maximally used
 * Return: the concatenated string
 */
char *_strncat(char *destination, char *source, int num_characters)
{
	int index_i, index_j;
	char *original_destination = destination;

	index_i = 0;
	index_j = 0;
	while (destination[index_i] != '\0')
		index_i++;
	while (source[index_j] != '\0' && index_j < num_characters)
	{
		destination[index_i] = source[index_j];
		index_i++;
		index_j++;
	}
	if (index_j < num_characters)
		destination[index_i] = '\0';
	return (original_destination);
}

/**
 * _strchr - locates a character in a string
 * @s: the string to be parsed
 * @c: the character to look for
 * Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
