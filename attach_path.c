#include "shell.h"

/**
* attach_path - adds path to command
* @path: path of command
* @cmd: user entered command
*
* Return: buffer containing command with path on success
* NULL on failure
*/
char *attach_path(char *path, char *cmd)
{
	char *buf;
	size_t t = 0, n = 0;

	if (cmd == 0)
		cmd = "";

	if (path == 0)
		path = "";

	buf = malloc(sizeof(char) * (_strlen(path) + _strlen(cmd) + 2));
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
	while (cmd[n])
	{
		buf[t + n] = cmd[n];
		n++;
	}
	buf[t + n] = '\0';
	return (buf);
}
