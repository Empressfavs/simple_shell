#include "shell.h"

/**
 * _environment - prints the current environment
 * @info: Contains arguments used to maintain constant function prototype.
 * Return: Always 0
 */
int _environment(info_t *info)
{
	print_list(info->env);
	return (0);
}

/**
 * _getenviron - gets the value of an environment variable
 * @info: Contains arguments used to maintain constant function prototype.
 * @name: environment variable name
 * Return: the value
 */
char *_getenviron(info_t *info, const char *name)
{
	list_t *node = info->env;
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
 * _setenviron - Initialize a new environment variable
 * @info: Contains potential arguments used to maintain constant prototype
 *  Return: Always 0
 */
int _setenviron(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _unsetenviron - Remove an environment variable
 * @info: Contains arguments used to maintain constant function prototype.
 *  Return: Always 0
 */
int _unsetenviron(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * pop_env_list - populates environment linked list
 * @info: Contains arguments used to maintain constant function prototype.
 * Return: Always 0
 */
int pop_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
	{
		add_node(&node, environ[i], 0);
	info->env = node;
	}
	return (0);
}
