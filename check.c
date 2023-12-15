#include "shell.h"
/**
 *assess - checks to see weather its a built in function
 *checker- a function that checks to see its a builtin function
 *@cmd: tokenized user input
 *@b: line drived fromgetline function
 *Return: 1 if cmd excuted 0 if cmd is not executed
 */
int assess(char **cmd, char *b)
{
	if (handle_builtin(cmd, b))
		return (1);
	else if (**cmd == '/')
	{
		execution(cmd[0], cmd);
		return (1);
	}
	return (0);
}
