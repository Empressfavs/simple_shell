#include "shell.h"
/**
 *assess - checks to see weather its a built in function
 *@command: tokenized user input
 *@b: line drived fromgetline function
 *Return: 1 if cmd excuted 0 if cmd is not executed
 */
int assess(char **command, char *b)
{
	if (secure_inbuilt(command, b))
		return (1);
	else if (**command == '/')
	{
		execution(command[0], command);
		return (1);
	}
	return (0);
}
