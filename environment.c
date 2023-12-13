#include "shell.h"

/**
 * _environment - prints the current environment
 * @data: Contains arguments used to maintain constant function prototype.
 * Return: Always 0
 */
int _environment(info_t *data)
{
	print_list(data->env);
	return (0);
}

/**
 * _getenviron - gets the value of an environment variable
 * @data: Contains arguments used to maintain constant function prototype.
 * @name: environment variable name
 * Return: the value
 */
char *_getenviron(info_t *data, const char *name)
{
	list_t *node = data->env;
	char *s;

	while (node)
	{
		s = starts_with(node->str, name);
		if (s && *s)
			return (s);
		node = node->next;
	}
	return (NULL);
}

/**
 * _setenviron - Initialize a new environment variable or modify an existing one
 * @data: Contains potential arguments used to maintain constant function prototype.
 *  Return: Always 0
 */
int _setenviron(info_t *data)
{
	if (data->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(data, data->argv[1], data->argv[2]))
		return (0);
	return (1);
}

/**
 * _unsetenviron - Remove an environment variable
 * @data: Contains arguments used to maintain constant function prototype.
 *  Return: Always 0
 */
int _unsetenviron(info_t *data)
{
	int i;

	if (data->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= data->argc; i++)
		_unsetenv(data, data->argv[i]);

	return (0);
}

/**
 * pop_env_list - populates environment linked list
 * @data: Contains arguments used to maintain constant function prototype.
 * Return: Always 0
 */
int pop_env_list(info_t *data)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
	{
		add_node(&node, environ[i], 0);
	data->env = node;
	}
	return (0);
}
