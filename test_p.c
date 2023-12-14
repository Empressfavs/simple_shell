#include "shell.h"
/**
* test_path - checks whether path is valid or not
* @path: tokenized path
* @cmd: command for user to enter
* Return: path appended with command on success
* NULL on failure
*/
char *test_path(char **path, char *cmd)
{
	int i = 0;
	char *output;

	while (path[i])
	{
		output = append_path(path[i], cmd);
		if (access(output, F_OK | X_OK) == 0)
			return (output);
		free(output);
		i++;
	}
	return (NULL);
}
