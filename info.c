#include "shell.h"

/**
 * clear_info - initializes info_t struct
 * @inf: struct address
 */
void clear_info(info_t *inf)
{
	inf->arg = NULL;
	inf->argv = NULL;
	inf->path = NULL;
	inf->argc = 0;
}

/**
 * set_info - initializes info_t struct
 * @inf: struct address
 * @arv: argument vector
 */
void set_info(info_t *info, char **arv)
{
	int i = 0;

	info->fname = arv[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdupli(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		rep_alias(info);
		rep_vars(info);
	}
}

/**
 * free_info - frees info_t
 * @info: struct address
 * @eve: true if freeing every fields
 */
void free_info(info_t *info, int eve)
{
	_free(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (eve)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_node(&(info->env));
		if (info->history)
			free_node(&(info->history));
		if (info->alias)
			free_node(&(info->alias));
		_free(info->environ);
			info->environ = NULL;
		mfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
