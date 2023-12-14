#include "shell.h"

/**
 *signal- it keeps track is interactive mode
 *@s: the signal number
 *Return: nothing
 */

void signal(int s)
{
	(void)s;
	write(STDERR_FILENO, "\n", 1);
	write(STDERR_FILENO, "$ ", 2);
}
