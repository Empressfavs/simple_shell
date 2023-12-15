#include "shell.h"

/**
* attach_path - adds path to command
* @path: path of command
* @cmd: user entered command
* Return: buffer containing command with path on success
* NULL on failure
*/
char *attach_path(char *path, char *cmd)
{
	char *b;
	size_t i = 0, j = 0;

	if (cmd == 0)
		cmd = "";

	if (path == 0)
		path = "";

	b = malloc(sizeof(char) * (_strlen(path) + _strlen(cmd) + 2));
	if (!b)
		return (NULL);

	while (path[i])
	{
		b[i] = path[i];
		i++;
	}

	if (path[i - 1] != '/')
	{
		b[i] = '/';
		i++;
	}
	while (cmd[j])
	{
		b[i + j] = cmd[j];
		j++;
	}
	b[i + j] = '\0';
	return (b);
}
