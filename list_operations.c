#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @head_ptr: address of pointer to head node
 * @str_field: str field of node
 * @node_index: node index used by history
 *
 * Return: pointer to the new node, NULL on failure
 */
list_t *add_node(list_t **head_ptr, const char *str_field, int node_index)
{
    if (!head_ptr)
        return NULL;

    list_t *new_node = malloc(sizeof(list_t));
    if (!new_node)
        return NULL;

    new_node->node_index = node_index;
    new_node->str_field = (str_field) ? _strdup(str_field) : NULL;
    new_node->next = *head_ptr;
    *head_ptr = new_node;

    return new_node;
}

/**
 * add_node_end - adds a node to the end of the list
 * @head_ptr: address of pointer to head node
 * @str_field: str field of node
 * @node_index: node index used by history
 *
 * Return: pointer to the new node, NULL on failure
 */
list_t *add_node_end(list_t **head_ptr, const char *str_field, int node_index)
{
    if (!head_ptr)
        return NULL;

    list_t *new_node = malloc(sizeof(list_t));
    if (!new_node)
        return NULL;

    new_node->node_index = node_index;
    new_node->str_field = (str_field) ? _strdup(str_field) : NULL;
    new_node->next = NULL;

    if (*head_ptr)
    {
        list_t *current = *head_ptr;
        while (current->next)
            current = current->next;
        current->next = new_node;
    }
    else
    {
        *head_ptr = new_node;
    }

    return new_node;
}

/**
 * print_list_str - prints only the str_field element of a list_t linked list
 * @node: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *node)
{
    size_t count = 0;

    while (node)
    {
        _puts((node->str_field) ? node->str_field : "(nil)");
        _puts("\n");
        node = node->next;
        count++;
    }

    return count;
}

/**
 * delete_node_at_index - deletes node at given target_index
 * @head_ptr: address of pointer to first node
 * @target_index: target_index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head_ptr, unsigned int target_index)
{
    if (!head_ptr || !*head_ptr)
        return 0;

    if (target_index == 0)
    {
        list_t *node_to_delete = *head_ptr;
        *head_ptr = (*head_ptr)->next;
        free(node_to_delete->str_field);
        free(node_to_delete);
        return 1;
    }

    list_t *current = *head_ptr;
    list_t *previous = NULL;
    unsigned int i = 0;

    while (current)
    {
        if (i == target_index)
        {
            previous->next = current->next;
            free(current->str_field);
            free(current);
            return 1;
        }

        i++;
        previous = current;
        current = current->next;
    }

    return 0;
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
    if (!head_ptr)
        return;

    list_t *current = *head_ptr;

    while (current)
    {
        list_t *next = current->next;
        free(current->str_field);
        free(current);
        current = next;
    }

    *head_ptr = NULL;
}
