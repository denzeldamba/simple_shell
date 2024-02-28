#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @shell_info: Structure containing potential arguments.
 * Return: Copy of the environment variables.
 */
char **get_environ(shell_info_t *shell_info)
{
    if (!shell_info->environment || shell_info->environment_changed)
    {
        char **environment_copy = duplicate_environment(shell_info->env);
        if (environment_copy)
        {
            free_string_array(shell_info->environment);
            shell_info->environment = environment_copy;
            shell_info->environment_changed = 0;
        }
    }
    return (shell_info->environment);
}

/**
 * _unsetenv - Remove an environment variable
 * @shell_info: Structure containing potential arguments.
 * @variable_name: The environment variable to unset.
 * Return: 1 on successful unset, 0 otherwise.
 */
int _unsetenv(shell_info_t *shell_info, const char *variable_name)
{
    if (!shell_info->environment || !variable_name)
        return 0;

    int is_removed = delete_environment_variable(&(shell_info->environment), variable_name);
    if (is_removed)
        shell_info->environment_changed = 1;

    return is_removed;
}

/**
 * _setenv - Initialize a new environment variable or modify an existing one.
 * @shell_info: Structure containing potential arguments.
 * @variable_name: The environment variable name.
 * @variable_value: The environment variable value.
 * Return: 0 on success, -1 on failure.
 */
int _setenv(shell_info_t *shell_info, const char *variable_name, const char *variable_value)
{
    if (!variable_name || !variable_value)
        return -1;

    char *environment_variable = create_environment_variable(variable_name, variable_value);
    if (!environment_variable)
        return -1;

    int is_updated = update_environment_variable(&(shell_info->environment), environment_variable);

    if (is_updated)
    {
        shell_info->environment_changed = 1;
    }
    else
    {
        add_node_end(&(shell_info->environment), environment_variable);
        free(environment_variable);
        shell_info->environment_changed = 1;
    }

    return 0;
}

