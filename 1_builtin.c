#include "shell.h"

/**
 * _myhistory - displays the history list, one command by line
 * @info: ContainS arguments used to maintain constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - unset alias from string
 * @info: struct parameter
 * @str: the string alias
 *
 * Return: Always 0 on success or 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *s, c;
	int cha;

	s = _strchr(str, '=');
	if (!s)
		return (1);
	c = *s;
	*s = 0;
	cha = delete_node(&(info->alias),
		node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*s = c;
	return (cha);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *s;

	s = _strchr(str, '=');
	if (!s)
		return (1);
	if (!*++s)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *s = NULL, *c = NULL;

	if (node)
	{
		s = _strchr(node->str, '=');
		for (c = node->str; c <= s; c++)
			_putchar(*c);
		_putchar('\'');
		_puts(s + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _alias - man alias
 * @info: Contains arguments used to maintain constant function prototype.
 *  Return: Always 0
 */
int _alias(info_t *info)
{
	int i = 0;
	char *s = NULL;
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
		s = _strchr(info->argv[i], '=');
		if (s)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
