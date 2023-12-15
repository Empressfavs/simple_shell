#include "shell.h"

/**
<<<<<<< HEAD
* attach_path - adds path to command
* @path: path of command
* @cmd: user entered command
*
=======
* append_path - a function that adds path to command
* @path: path of command
* @command: user entered command
>>>>>>> e9c18e9f7287a193e1522a41fd5d8ed48d2bfd93
* Return: buffer containing command with path on success
* NULL on failure
*/
char *attach_path(char *path, char *cmd)
{
	char *b;
	size_t i = 0, j = 0;

	if (command == 0)
		command = "";

	if (path == 0)
		path = "";

	buf = malloc(sizeof(char) * (_strlen(path) + _strlen(cmd) + 2));
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
