#include "shell.h"
/**
 *check- checks to see weather its a built-in function
 *@cmd: tokenized user input
 *@buf: line drived from getline function
 *Return: 1 if cmd excuted 0 if cmd is not executed
 */
int check(char **cmd, char *buf)
{
	if (handle_builtin(cmd, buf))
		return (1);
	else if (**cmd == '/')
	{
		execution(cmd[0], cmd);
		return (1);
	}
	return (0);
}
