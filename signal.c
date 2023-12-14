#include "shell.h"

/**
 *handle_signal- a function that keeps track of interactive mode
 *@s: the signal number
 *Return: nothing
 */

void handle_signal(int s)
{
	(void)s;
	write(STDERR_FILENO, "\n", 1);
	write(STDERR_FILENO, "$ ", 2);
}
