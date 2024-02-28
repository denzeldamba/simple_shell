##include "shell.h"

/**
 * list_len - determines length of linked list
 * @node: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *node)
{
    size_t list_length = 0;

    while (node)
    {
        node = node->next;
        list_length++;
    }
    return list_length;
}

/**
 * list_to_strings - returns an array of strings of the node->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
    size_t list_length = list_len(head);

    if (!head || list_length == 0)
        return NULL;

    char **string_array = malloc(sizeof(char *) * (list_length + 1));
    if (!string_array)
        return NULL;

    size_t index = 0;
    while (head)
    {
        string_array[index] = _strdup(head->str);
        if (!string_array[index])
        {
            for (size_t j = 0; j < index; j++)
                free(string_array[j]);
            free(string_array);
            return NULL;
        }
        head = head->next;
        index++;
    }

    string_array[index] = NULL;
    return string_array;
}

/**
 * print_list - prints all elements of a list_t linked list
 * @node: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *node)
{
    size_t list_length = 0;

    while (node)
    {
        _puts(convert_number(node->num, 10, 0));
        _puts(": ");
        _puts(node->str ? node->str : "(nil)");
        _puts("\n");
        node = node->next;
        list_length++;
    }
    return list_length;
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
    while (node)
    {
        char *p = starts_with(node->str, prefix);
        if (p && ((c == -1) || (*p == c)))
            return node;
        node = node->next;
    }
    return NULL;
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
    ssize_t index = 0;

    while (head)
    {
        if (head == node)
            return index;
        head = head->next;
        index++;
    }
    return -1;
}
