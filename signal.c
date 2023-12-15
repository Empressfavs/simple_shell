#include "shell.h"

/**
 *secure_signal- it keeps track is interactive mode
 *handle_signal- a function that keeps track if it is interactive mode
 *@m: the signal number
 *Return: nothing
 */

void secure_signal(int m)
{
	(void)m;
	write(STDERR_FILENO, "\n", 1);
	write(STDERR_FILENO, "$ ", 2);
}
