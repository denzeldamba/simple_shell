#include "shell.h"

/**
 * _print_current_environment - Prints the current environment.
 * @shell_info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0.
 */
int _print_current_environment(info_t *shell_info)
{
    print_list_str(shell_info->env);
    return 0;
}

/**
 * _get_env_variable - Gets the value of an environment variable.
 * @shell_info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @variable_name: Environment variable name.
 * Return: The value of the variable or NULL if not found.
 */
char *_get_env_variable(info_t *shell_info, const char *variable_name)
{
    list_t *current_node = shell_info->env;
    while (current_node)
    {
        char *variable_str = current_node->str;
        if (_strncmp(variable_str, variable_name, _str_len(variable_name)) == 0 && variable_str[_str_len(variable_name)] == '=')
            return variable_str + _str_len(variable_name) + 1;
        current_node = current_node->next;
    }
    return NULL;
}

/**
 * _initialize_env_variable - Initialize a new environment variable
 *                           or modify an existing one.
 * @shell_info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0.
 */
int _initialize_env_variable(info_t *shell_info)
{
    if (shell_info->argc != 3)
    {
        _eprint("Incorrect number of arguments\n");
        return 1;
    }
    if (_set_env_variable(shell_info, shell_info->argv[1], shell_info->argv[2]) == 0)
    {
        _eprint("Failed to set environment variable\n");
        return 1;
    }
    return 0;
}

/**
 * _remove_env_variable - Remove an environment variable.
 * @shell_info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0.
 */
int _remove_env_variable(info_t *shell_info)
{
    if (shell_info->argc == 1)
    {
        _eprint("Too few arguments.\n");
        return 1;
    }
    for (int i = 1; i < shell_info->argc; i++)
    {
        if (_unset_env_variable(shell_info, shell_info->argv[i]) == 0)
        {
            _eprint("Failed to unset environment variable\n");
            return 1;
        }
    }
    return 0;
}

/**
 * _populate_env_list - Populates the environment linked list.
 * @shell_info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0.
 */
int _populate_env_list(info_t *shell_info)
{
    shell_info->env = NULL;
    for (char **env = environ; *env != NULL; env++)
        add_node_end(&(shell_info->env), *env, 0);
    return 0;
}