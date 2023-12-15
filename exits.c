#include "shell.h"

/**
* exit_cmd - a function that handles the exit command
* @command: tokenized command
* @line: input read from standard input
*
* Return: no return
*/
void exit_cmd(char **command, char *line)
{
	free(line);
	free_buffers(command);
	exit(0);
}
