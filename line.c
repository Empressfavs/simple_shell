#include "shell.h"

/**
 * input_buff - buffers chained commands
 * @inf: parameter
 * @buff: address of the buffer
 * @len: address of the length variable
 * Return: bytes read
 */
ssize_t input_buff(info_t *inf, char **buff, size_t *len)
{
	ssize_t t = 0;
	size_t len_t = 0;

	if (!*len)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		t = getline(buff, &len_t, stdin);
#else
		t = _line(inf, buff, &len_t);
#endif
		if (t > 0)
		{
			if ((*buff)[t - 1] == '\n')
			{
				(*buff)[t - 1] = '\0';
				t--;
			}
			inf->linecount_flag = 1;
			rem_comments(*buff);
			history_list(inf, *buff, inf->histcount++);
			{
				*len = t;
				inf->cmd_buf = buff;
			}
		}
	}
	return (t);
}

/**
 * _input - gets a line minus the newline
 * @inf: parameter struct
 *
 * Return: bytes read
 */
ssize_t _input(info_t *inf)
{
	static char *buff;
	static size_t i, j, len;
	ssize_t t = 0;
	char **buf_f = &(inf->arg), *c;

	_putchar(BUF_FLUSH);
	t = input_buff(inf, &buff, &len);
	if (t == -1)
		return (-1);
	if (len)
	{
		j = i;
		c = buff + i;

		check_chain(inf, buff, &j, i, len);
		while (j < len)
		{
			if (is_chain(inf, buff, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			inf->cmd_buf_type = CMD_NORM;
		}

		*buf_f = c;
		return (_str_len(c));
	}

	*buf_f = buff;
	return (t);
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buff: buffer
 * @i: size
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buff, size_t *i)
{
	ssize_t t = 0;

	if (*i)
		return (0);
	t = read(info->readfd, buff, READ_BUF_SIZE);
	if (t >= 0)
		*i = t;
	return (t);
}

/**
 * _line - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @len: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _line(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t t, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (t == len)
		t = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + t, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _reallocate(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + t, k - t);
	else
		_strncpy(new_p, buf + t, k - t + 1);

	s += k - t;
	t = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

