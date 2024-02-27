#include "shell.h"

/**
 * exit_shell - Exits the shell.
 * @info: Structure containing potential arguments Used to maintain
 *        constant function prototype
 * Return: Exits with a given exit status (0) if info->argv[0] != "exit".
 */
int exit_shell(info_t *info)
{
    if (info->argv[1]) /* If there is an exit argument */
    {
        int exit_code = _erratoi(info->argv[1]);
        if (exit_code == -1)
        {
            info->status = 2;
            print_error(info, "Illegal number: %s\n", info->argv[1]);
            return 1;
        }
        info->err_num = exit_code;
        return -2;
    }
    info->err_num = -1;
    return -2;
}

/**
 * change_directory - Changes the current directory of the process.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0.
 */
int change_directory(info_t *info)
{
    char buffer[1024];
    char *dir;
    int chdir_ret;

    char *current_directory = getcwd(buffer, 1024);
    if (!current_directory)
        _puts("TODO: >>getcwd failure emsg here<<\n");

    if (!info->argv[1])
    {
        dir = _getenv(info, "HOME=");
        if (!dir)
            dir = _getenv(info, "PWD=");

        chdir_ret = chdir(dir ? dir : "/");
    }
    else if (_strcmp(info->argv[1], "-") == 0)
    {
        char *old_pwd = _getenv(info, "OLDPWD=");
        if (!old_pwd)
        {
            _puts(current_directory);
            _putchar('\n');
            return 1;
        }
        _puts(old_pwd), _putchar('\n');
        chdir_ret = chdir(old_pwd ? old_pwd : "/");
    }
    else
    {
        chdir_ret = chdir(info->argv[1]);
    }

    if (chdir_ret == -1)
    {
        print_error(info, "can't cd to %s\n", info->argv[1]);
    }
    else
    {
        _setenv(info, "OLDPWD", _getenv(info, "PWD="));
        _setenv(info, "PWD", getcwd(buffer, 1024));
    }
    return 0;
}

/**
 * print_help - Provides help information.
 * @info: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * Return: Always 0.
 */
int print_help(info_t *info)
{
    char **arg_array = info->argv;
    _puts("help call works. Function not yet implemented\n");
    if (0)
        _puts(*arg_array); /* temp att_unused workaround */
    return 0;
}
