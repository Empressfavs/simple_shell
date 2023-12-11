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
		inf->environ = list_to_strings(inf->env);
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
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			inf->env_changed = delete_node_at_index(&(inf->env), t);
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
int _setenv(info_t *inf, char *var, char *val)
{
	char *buf = NULL;
	list_t *node;
	char *c;

	if (!var || !val)
		return (0);

	buf = malloc(_strlen(var) + _strlen(val) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, val);
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
	add_node_end(&(inf->env), buf, 0);
	free(buf);
	inf->env_changed = 1;
	return (0);
}

