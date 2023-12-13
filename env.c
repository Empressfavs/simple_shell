#include "shell.h"

/**
 * get_env - returns the string array copy of our environ
 * @inf: Contains arguments used to maintain constant function prototype.
 * Return: Always 0
 */
char **get_env(info_t *inf)
{
	if (!inf->environ || inf->env_changed)
	{
		inf->environ = list_str(inf->env);
		inf->env_changed = 0;
	}

	return (inf->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @inf: Contains arguments used to maintain constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string environment variable property
 */
int _unsetenv(info_t *inf, char *var)
{
	list_t *node = inf->env;
	size_t t = 0;
	char *c;

	if (!node || !var)
		return (0);

	while (node)
	{
		c = starts_with(node->str, var);
		if (c && *c == '=')
		{
			inf->env_changed = delete_node(&(inf->env), t);
			t = 0;
			node = inf->env;
			continue;
		}
		node = node->next;
		t++;
	}
	return (inf->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @inf: Containing potential arguments used to maintain constant function prototype.
 * @var: the string environment variable property
 * @val: the string environment variable value
 *  Return: Always 0
 */
int _setenv(info_t *inf, char *var, char *value)
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
	node = inf->env;
	while (node)
	{
		c = starts_with(node->str, var);
		if (c && *c == '=')
		{
			free(node->str);
			node->str = buf;
			inf->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node(&(inf->env), buf, 0);
	free(buf);
	inf->env_changed = 1;
	return (0);
}

