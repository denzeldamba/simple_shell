#include "shell.h"

/**
 * set_memory - fills memory with a constant byte
 * @dest: the pointer to the memory area
 * @ch: the byte to fill *dest with
 * @n: the amount of bytes to be filled
 * Return: a pointer to the memory area dest
 */
char *set_memory(char *dest, char ch, unsigned int n)
{
    char *p = dest;

    while (n--)
    {
        *p = ch;
        p++;
    }

    return dest;
}

/**
 * free_string_array - frees a string array
 * @str_array: string array to free
 */
void free_string_array(char **str_array)
{
    if (!str_array)
        return;

    char **temp = str_array;
    while (*str_array)
    {
        free(*str_array);
        str_array++;
    }

    free(temp);
}

/**
 * reallocate_memory - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to the reallocated block of memory
 */
void *reallocate_memory(void *ptr, unsigned int old_size, unsigned int new_size)
{
    char *new_ptr = NULL;

    if (!ptr)
        return malloc(new_size);

    if (!new_size)
    {
        free(ptr);
        return NULL;
    }

    if (new_size == old_size)
        return ptr;

    new_ptr = malloc(new_size);
    if (!new_ptr)
        return NULL;

    for (unsigned int i = 0; i < old_size && i < new_size; i++)
        new_ptr[i] = ((char *)ptr)[i];

    free(ptr);
    return new_ptr;
}
