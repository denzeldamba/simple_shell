#include "shell.h"

/**
 * is_executable - determines if a file is an executable command
 * @info: the info struct
 * @file_path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_executable(info_t *info, char *file_path)
{
    struct stat st;

    (void)info;
    if (!file_path || stat(file_path, &st) == -1)
        return 0;

    return S_ISREG(st.st_mode) ? 1 : 0;
}

/**
 * duplicate_chars - duplicates characters
 * @path_str: the PATH string
 * @start_index: starting index
 * @stop_index: stopping index
 *
 * Return: pointer to new buffer
 */
char *duplicate_chars(const char *path_str, int start_index, int stop_index)
{
    char *buffer = malloc(stop_index - start_index + 1);
    if (!buffer)
        return NULL;

    int buffer_index = 0;
    for (int index = start_index; index < stop_index; index++)
    {
        if (path_str[index] != ':')
            buffer[buffer_index++] = path_str[index];
    }
    buffer[buffer_index] = '\0';

    return buffer;
}

/**
 * find_executable - finds the full path of an executable command in the PATH string
 * @info: the info struct
 * @path_str: the PATH string
 * @command: the command to find
 *
 * Return: full path of command if found or NULL
 */
char *find_executable(info_t *info, char *path_str, char *command)
{
    if (!path_str)
        return NULL;

    if ((_strlen(command) > 2) && starts_with(command, "./"))
    {
        if (is_executable(info, command))
            return command;
    }

    int index = 0;
    int current_position = 0;
    char *path = NULL;

    while (1)
    {
        if (!path_str[index] || path_str[index] == ':')
        {
            path = duplicate_chars(path_str, current_position, index);
            if (!*path)
                _strcat(path, command);
            else
            {
                _strcat(path, "/");
                _strcat(path, command);
            }
            if (is_executable(info, path))
                return path;

            if (!path_str[index])
                break;
            current_position = index;
        }
        index++;
    }

    return NULL;
}
