#include "shell.h"

/**
 * get_env - returns the string array copy of our environ
 * @info: Contains arguments used to maintain constant function prototype.
 * Return: Always 0
 */
char **get_env(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_str(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Contains arguments used to maintain constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string environment variable property
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t t = 0;
	char *c;

	if (!node || !var)
		return (0);

	while (node)
	{
		c = starts_with(node->str, var);
		if (c && *c == '=')
		{
			info->env_changed = delete_node(&(info->env), t);
			t = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		t++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Contains arguments used to maintain constant function prototype.
 * @var: the string environment variable property
 * @value: the string environment variable value
 * Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *c;

	if (!var || !value)
		return (0);

	buf = malloc(_str_len(var) + _str_len(value) + 2);
	if (!buf)
		return (1);
	_str_cpy(buf, var);
	_str_cat(buf, "=");
	_str_cat(buf, value);
	node = info->env;
	while (node)
	{
		c = starts_with(node->str, var);
		if (c && *c == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
