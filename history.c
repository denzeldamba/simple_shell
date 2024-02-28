#include "shell.h"

/**
 * get_history_file - gets the history file
 * @info_struct: parameter struct
 *
 * Return: allocated string containing history file
 */
char *get_history_file(info_t *info_struct)
{
    char *home_dir = _getenv(info_struct, "HOME=");
    if (!home_dir)
        return NULL;

    char *history_file = _strcat(home_dir, "/" HIST_FILE);
    free(home_dir);

    return history_file;
}

/**
 * write_history - creates a file, or appends to an existing file
 * @info_struct: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info_struct)
{
    char *history_file = get_history_file(info_struct);
    if (!history_file)
        return -1;

    int fd = open(history_file, O_CREAT | O_WRONLY | O_APPEND, 0644);
    free(history_file);

    if (fd == -1)
        return -1;

    list_t *history_node = info_struct->history;
    while (history_node)
    {
        _putsfd(history_node->str, fd);
        _putfd('\n', fd);
        history_node = history_node->next;
    }

    close(fd);
    return 1;
}

/**
 * read_history - reads history from file
 * @info_struct: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info_struct)
{
    char *history_file = get_history_file(info_struct);
    if (!history_file)
        return 0;

    int fd = open(history_file, O_RDONLY);
    free(history_file);

    if (fd == -1)
        return 0;

    struct stat file_stat;
    if (fstat(fd, &file_stat) != 0 || file_stat.st_size < 2)
    {
        close(fd);
        return 0;
    }

    char *history_buffer = (char *)malloc(file_stat.st_size + 1);
    if (!history_buffer)
    {
        close(fd);
        return 0;
    }

    ssize_t read_length = read(fd, history_buffer, file_stat.st_size);
    close(fd);

    if (read_length <= 0)
    {
        free(history_buffer);
        return 0;
    }

    history_buffer[file_stat.st_size] = '\0';

    int last_index = 0;
    int history_line_count = 0;
    for (int index = 0; index < read_length; index++)
    {
        if (history_buffer[index] == '\n')
        {
            history_buffer[index] = '\0';
            build_history_list(info_struct, history_buffer + last_index, history_line_count++);
            last_index = index + 1;
        }
    }

    if (last_index != read_length)
        build_history_list(info_struct, history_buffer + last_index, history_line_count++);

    free(history_buffer);

    info_struct->histcount = history_line_count;

    while (info_struct->histcount-- >= MAX_HISTORY_SIZE)
        delete_node_at_index(&(info_struct->history), 0);

    renumber_history(info_struct);

    return info_struct->histcount;
}

/**
 * build_history_list - adds entry to a history linked list
 * @info_struct: Structure containing potential arguments.
 * @history_buffer: buffer
 * @history_line_count: the history line count, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info_struct, char *history_buffer, int history_line_count)
{
    add_node_end(&(info_struct->history), history_buffer, history_line_count);
    return 0;
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info_struct: Structure containing potential arguments.
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info_struct)
{
    list_t *history_node = info_struct->history;
    int index = 0;

    while (history_node)
    {
        history_node->num = index++;
        history_node = history_node->next;
    }

    return (info_struct->histcount = index);
}
