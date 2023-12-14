#include "shell.h"

/**
* tokenizer - creates tokens from given input
* @line: input to be tokenized
* Return: array of strings
*/
char **tokenizer(char *line)
{
	char *buf = NULL, *buff = NULL, *token = NULL, *del = " :\t\r\n";
	char **tokens = NULL;
	int tokensize = 1;
	size_t index = 0, flag = 0;

	buf = _strdup(line);
	if (!buf)
		return (NULL);
	buff = buf;

	while (*buff)
	{
		if (_strchr(del, *buff) != NULL && flag == 0)
		{
			tokensize++;
			flag = 1;
		}
		else if (_strchr(del, *buff) == NULL && flag == 1)
			flag = 0;
		buff++;
	}
	tokens = malloc(sizeof(char *) * (tokensize + 1));
	token = strtok(buf, del);
	while (token)
	{
		tokens[index] = _strdup(token);
		if (tokens[index] == NULL)
		{
			free(tokens);
			return (NULL);
		}
		token = strtok(NULL, del);
		index++;
	}
	tokens[index] = '\0';
	free(buf);
	return (tokens);
}
