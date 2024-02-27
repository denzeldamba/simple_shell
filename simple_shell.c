#include "holberton.h"

/**
 * start_shell - Starts the simple shell
 *
 * Return: Always 0 (success)
 */
int start_shell(void)
{
	char *prompt = "$ ";

	while (1)
	{
		display_prompt(prompt);

		char *user_input = read_user_input();

		if (user_input == NULL)
			break;

		char *command_string = tokenize_input(user_input);

		pid_t child_pid = create_child_process();

		if (child_pid == 0)
			execute_command(command_string);
		else
			wait_for_child_process(child_pid);
	}

	return (0);
}