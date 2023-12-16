#include "shell.h"
/**
 * _myhistory - displays the history list
 * @info: contains potential arguments
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int uns;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	uns = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (uns);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *c;

	c = _strchr(str, '=');
	if (!c)
		return (1);
	if (!*++c)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *c = NULL, *a = NULL;

	if (node)
	{
		c = _strchr(node->str, '=');
		for (a = node->str; a <= c; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(c + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin
 * @info: Contains potential arguments.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *c = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		c = _strchr(info->argv[i], '=');
		if (c)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
