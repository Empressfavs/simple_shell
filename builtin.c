#include "shell.h"

/**
* secure_inbuilt - handles execution of builtin functions
* @cmd: tokenized commands
* @line: input read from stdin
* Return: 1 if executed, 0 if not
*/
int secure_inbuilt(char **cmd, char *line)
{
	struct builtin builtin = {"env", "exit"};

	if (_strcmp(*cmd, builtin.env) == 0)
	{
		print_env();
		return (1);
	}
	else if (_strcmp(*cmd, builtin.exit) == 0)
	{
		exit_cmd(cmd, line);
		return (1);
	}
	return (0);
}
