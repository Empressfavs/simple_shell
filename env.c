#include "shell.h"

/**
 * _ourenv - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _ourenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *n = info->env;
	char *p;

	while (n)
	{
		p = starts_with(n->str, name);
		if (p && *p)
			return (p);
		n = n->next;
	}
	return (NULL);
}

/**
 * _oursetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _oursetenv(info_t *info)
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
 * _ourunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _ourunsetenv(info_t *info)
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
 * populate_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _env_list(info_t *info)
{
	list_t *n = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_n_end(&n, environ[i], 0);
	info->env = n;
	return (0);
}

