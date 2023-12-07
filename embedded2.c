#include "shell.h"

/**
 * _history - displays the history list, one command by line
 * @data: ContainS arguments used to maintain constant function prototype.
 *  Return: Always 0
 */
int _history(data_t *data)
{
	print_list(data->history);
	return (0);
}

/**
 * unset_alias - unset alias from string
 * @data: struct parameter
 * @str: the string alias
 *
 * Return: Always 0 on success or 1 on error
 */
int unset_alias(data_t *data, char *str)
{
	char *s, c;
	int cha;

	s = _strchr(str, '=');
	if (!s)
		return (1);
	c = *s;
	*s = 0;
	cha = delete_node_at_index(&(data->alias),
		get_node_index(data->alias, node_starts_with(data->alias, str, -1)));
	*s = c;
	return (cha);
}

/**
 * set_alias - sets alias to string
 * @data: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(data_t *data, char *str)
{
	char *s;

	s = _strchr(str, '=');
	if (!s)
		return (1);
	if (!*++s)
		return (unset_alias(data, str));

	unset_alias(data, str);
	return (add_node_end(&(data->alias), str, 0) == NULL);
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
 * @data: Contains arguments used to maintain constant function prototype.
 *  Return: Always 0
 */
int _alias(data_t *data)
{
	int i = 0;
	char *s = NULL;
	list_t *node = NULL;

	if (data->argc == 1)
	{
		node = data->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; data->argv[i]; i++)
	{
		s = _strchr(data->argv[i], '=');
		if (s)
			set_alias(data, data->argv[i]);
		else
			print_alias(node_starts_with(data->alias, data->argv[i], '='));
	}

	return (0);
}
