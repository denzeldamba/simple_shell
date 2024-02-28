#include "shell.h"

int execute_shell(info_t *shell_info, char **arguments)
{
    ssize_t read_bytes;
    int builtin_return;

    // Loop until an exit condition is met
    while (read_bytes != -1 && builtin_return != -2)
    {
        clear_info(shell_info);
        if (is_interactive(shell_info))
            _puts("$ ");
        _eputchar(BUF_FLUSH);
        read_bytes = get_input(shell_info);

        if (read_bytes != -1)
        {
            set_shell_info(shell_info, arguments);
            builtin_return = find_builtin_command(shell_info);

            if (builtin_return == -1)
                find_command(shell_info);
        }
        else if (is_interactive(shell_info))
            _putchar('\n');

        free_shell_info(shell_info, 0);
    }

    write_history(shell_info);
    free_shell_info(shell_info, 1);

    if (!is_interactive(shell_info) && shell_info->status)
        exit(shell_info->status);

    if (builtin_return == -2)
    {
        if (shell_info->error_num == -1)
            exit(shell_info->status);
        exit(shell_info->error_num);
    }

    return (builtin_return);
}

int find_builtin_command(info_t *shell_info)
{
    int i, builtin_return = -1;
    builtin_table builtintbl[] = {
        {"exit", _myexit},
        {"env", _myenv},
        {"help", _myhelp},
        {"history", _myhistory},
        {"setenv", _mysetenv},
        {"unsetenv", _myunsetenv},
        {"cd", _mycd},
        {"alias", _myalias},
        {NULL, NULL}
    };

    // Check if the entered command is a built-in
    for (i = 0; builtintbl[i].type; i++)
    {
        if (_strcmp(shell_info->argv[0], builtintbl[i].type) == 0)
        {
            shell_info->line_count++;
            builtin_return = builtintbl[i].func(shell_info);
            break;
        }
    }

    return builtin_return;
}

void find_command(info_t *shell_info)
{
    char *path = NULL;
    int i, k;

    shell_info->path = shell_info->argv[0];

    if (shell_info->linecount_flag == 1)
    {
        shell_info->line_count++;
        shell_info->linecount_flag = 0;
    }

    // Count the number of non-delimiter characters in the argument
    for (i = 0, k = 0; shell_info->arg[i]; i++)
    {
        if (!is_delimiter(shell_info->arg[i], " \t\n"))
        {
            k++;
        }
    }

    if (!k)
    {
        return;
    }

    // Find the command in the PATH
    path = find_command_path(shell_info, _getenv(shell_info, "PATH="), shell_info->argv[0]);

    if (path)
    {
        shell_info->path = path;
        execute_command(shell_info);
    }
    else
    {
        if ((is_interactive(shell_info) || _getenv(shell_info, "PATH=") || shell_info->argv[0][0] == '/') && is_command(shell_info, shell_info->argv[0]))
        {
            execute_command(shell_info);
        }
        else if (*(shell_info->arg) != '\n')
        {
            shell_info->status = 127;
            print_error(shell_info, "not found\n");
        }
    }
}

void execute_command(info_t *shell_info)
{
    pid_t child_pid;

    // Fork a child process
    child_pid = fork();
    if (child_pid == -1)
    {
        perror("Error:");
        return;
    }

    if (child_pid == 0)
    {
        // Child process: execute the command
        if (execve(shell_info->path, shell_info->argv, get_environment(shell_info)) == -1)
        {
            free_shell_info(shell_info, 1);
            if (errno == EACCES)
                exit(126);
            exit(1);
        }
    }
    else
    {
        // Parent process: wait for the child to finish
        wait(&(shell_info->status));

        if (WIFEXITED(shell_info->status))
        {
            shell_info->status = WEXITSTATUS(shell_info->status);
            
            if (shell_info->status == 126)
                print_error(shell_info, "Permission denied\n");
        }
    }
}
