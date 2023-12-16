#include "shell.h"

/**
 * _myenv - A function that prints the current environment
 * @info: contains potential arguments
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - A function that gets the value of an environ variable
 * @info: contain potential arguments
 * @name: environment variable name
 * Return: the value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *c;

	while (node)
	{
		c = starts_with(node->str, name);
		if (c && *c)
			return (c);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - A function that initialize a new environment variable
 * @info: contains potential arguments
 *  Return: Always 0
 */
int _mysetenv(info_t *info)
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
 * _myunsetenv - A function that remove an environment variable
 * @info: contains potential arguments
 * Return: Always 0
 */
int _myunsetenv(info_t *info)
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
 * populate_env_list - A function that populates env linked list
 * @info: contains potential arguments.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t t;

	for (t = 0; environ[t]; t++)
		add_node_end(&node, environ[t], 0);
	info->env = node;
	return (0);
}
