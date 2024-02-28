#ifndef HOLBERTON_H
#define HOLBERTON_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

/** Function prototypes **/

void print_prompt(char *prompt);
char *read_line(void);
char *tokenize(char *input);
void execute(char *command);

/** Macro constants **/

#define READ_BUFFER 1024

/** Data Structures **/

/**
 * struct command_t - Structure for commands
 * @name: Name of command
 * @args: List of arguments
 */
typedef struct command_t
{
	char *name;
	char **args;
} command_t;

#endif /* HOLBERTON_H */
