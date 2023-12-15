#include "shell.h"

/**
* test_path - a function that checks if a path is valid or not
* @path: tokenized path
* @command: user entered command
* Return: path appended with command on success
* NULL on failure
*/
char *test_path(char **path, char *command)
{
	int i = 0;
	char *output;

	while (path[i])
	{
		output = attach_path(path[i], command);
		if (access(output, F_OK | X_OK) == 0)
			return (output);
		free(output);
		i++;
	}
	return (NULL);
}
