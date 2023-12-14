#include "shell.h"

/**
* append_path - a function that adds path to a command
* @path: path of command
* @command: command for user to enter
* Return: buffer containing command with path on success
* NULL on failure
*/
char *append_path(char *path, char *command)
{
	char *buf;
	size_t t = 0, n = 0;

	if (command == 0)
		command = "";

	if (path == 0)
		path = "";

	buf = malloc(sizeof(char) * (_strlen(path) + _strlen(command) + 2));
	if (!buf)
		return (NULL);

	while (path[t])
	{
		buf[t] = path[t];
		t++;
	}

	if (path[t - 1] != '/')
	{
		buf[t] = '/';
		t++;
	}
	while (command[n])
	{
		buf[t + n] = command[n];
		n++;
	}
	buf[t + n] = '\0';
	return (buf);
}
