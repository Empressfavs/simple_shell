#include "shell.h"

/**
 * list_len - determines length of the linked list
 * @n: pointer to first node
 * Return: size of list
 */
size_t list_len(const list_t *n)
{
	size_t t = 0;

	while (n)
	{
		n = n->next;
		t++;
	}
	return (t);
}

/**
 * list_str - returns an array of strings of the list
 * @head: pointer to first node
 * Return: array of strings
 */
char **list_str(list_t *head)
{
	list_t *node = head;
	size_t t = list_len(head), i;
	char **strs;
	char *str;

	if (!head || !t)
		return (NULL);
	strs = malloc(sizeof(char *) * (t + 1));
	if (!strs)
		return (NULL);
	for (t = 0; node; node = node->next, t++)
	{
		str = malloc(_str_len(node->str) + 1);
		if (!str)
		{
			for (i = 0; i < t; i++)
				free(strs[i]);
			free(strs);
			return (NULL);
		}

		str = _str_cpy(str, node->str);
		strs[t] = str;
	}
	strs[t] = NULL;
	return (strs);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @n: pointer to first node
 * Return: size of list
 */
size_t print_list(const list_t *n)
{
	size_t t = 0;

	while (n)
	{
		_puts(convert_num(n->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(n->str ? n->str : "(nil)");
		_puts("\n");
		n = n->next;
		t++;
	}
	return (t);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @pre: string to match
 * @c: the next character after prefix to match
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *pre, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, pre);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 * Return: index of node or -1
 */
ssize_t node_index(list_t *head, list_t *node)
{
	size_t t = 0;

	while (head)
	{
		if (head == node)
			return (t);
		head = head->next;
		t++;
	}
	return (-1);
}
