#include "shell.h"

/**
 * history_file - gets the history file
 * @info: parameter
 * Return: string containing history file
 */

char *history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenviron(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_str_len(dir) + _str_len(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_str_cpy(buf, dir);
	_str_cat(buf, "/");
	_str_cat(buf, HIST_FILE);
	return (buf);
}

/**
 * create_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 * Return: 1 on success otherwise -1
 */
int create_history(info_t *info)
{
	ssize_t fd;
	char *fname = history_file(info);
	list_t *node = NULL;

	if (!fname)
		return (-1);

	fd = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fname);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads the file history
 * @info: the parameter struct
 * Return: history_count on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *fname = history_file(info);

	if (!fname)
		return (0);
	fd = open(fname, O_RDONLY);
	free(fname);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
	{
		history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node(&(info->history), 0);
	renumber_history(info);
	}
	return (info->histcount);
}

/**
 * history_list - adds entry to a history linked list
 * @info: Contains arguments used to maintain function prototype
 * @buf: buffer
 * @linecount: the history linecount
 * Return: Always 0
 */
int history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
