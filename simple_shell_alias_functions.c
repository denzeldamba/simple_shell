#include "shell.h"

/**
 * _display_history - Displays the history list, one command per line, preceded
 *                    by line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _display_history(info_t *shell_info)
{
    list_t *current_node = shell_info->history;
    int line_number = 0;

    while (current_node)
    {
        _printf("%5d  %s\n", line_number++, current_node->str);
        current_node = current_node->next;
    }
    return 0;
}

/**
 * _unset_alias_variable - Unsets an alias variable.
 * @shell_info: Parameter struct.
 * @alias_str: The string alias.
 * Return: Always 0 on success, 1 on error.
 */
int _unset_alias_variable(info_t *shell_info, char *alias_str)
{
    char *equal_sign = _strchr(alias_str, '=');
    if (equal_sign)
    {
        *equal_sign = '\0';
        int removal_status = delete_node_by_value(&(shell_info->alias), alias_str);
        *equal_sign = '=';
        return removal_status;
    }
    return 1;
}

/**
 * _set_alias_variable - Sets or updates an alias variable.
 * @shell_info: Parameter struct.
 * @alias_str: The string alias.
 * Return: Always 0 on success, 1 on error.
 */
int _set_alias_variable(info_t *shell_info, char *alias_str)
{
    char *equal_sign = _strchr(alias_str, '=');
    if (equal_sign)
    {
        *equal_sign = '\0';
        _unset_alias_variable(shell_info, alias_str);
        return (add_node_end(&(shell_info->alias), alias_str, 0) == NULL);
    }
    return 1;
}

/**
 * _print_alias_node - Prints an alias string.
 * @alias_node: The alias node.
 * Return: Always 0 on success, 1 on error.
 */
int _print_alias_node(list_t *alias_node)
{
    if (alias_node)
    {
        char *equal_sign = _strchr(alias_node->str, '=');
        if (equal_sign)
        {
            *equal_sign = '\0';
            _printf("%s='%s'\n", alias_node->str, equal_sign + 1);
            *equal_sign = '=';
            return 0;
        }
    }
    return 1;
}

/**
 * _my_alias - Mimics the alias builtin (man alias).
 * @shell_info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0.
 */
int _my_alias(info_t *shell_info)
{
    if (shell_info->argc == 1)
    {
        list_t *current_node = shell_info->alias;
        while (current_node)
        {
            _print_alias_node(current_node);
            current_node = current_node->next;
        }
        return 0;
    }

    for (int i = 1; shell_info->argv[i]; i++)
    {
        char *equal_sign = _strchr(shell_info->argv[i], '=');
        if (equal_sign)
            _set_alias_variable(shell_info, shell_info->argv[i]);
        else
            _print_alias_node(node_starts_with(shell_info->alias, shell_info->argv[i], '='));
    }

    return 0;
}
