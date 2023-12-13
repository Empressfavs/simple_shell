#include "shell.h"

/**
 * clear_inf - initializes info_t struct
 * @inf: struct address
 */
void clear_inf(info_t *inf)
{
	inf->arg = NULL;
	inf->argv = NULL;
	inf->path = NULL;
	inf->argc = 0;
}

/**
 * set_inf - initializes info_t struct
 * @inf: struct address
 * @arv: argument vector
 */
void set_inf(info_t *inf, char **arv)
{
	int i = 0;

	inf->fname = arv[0];
	if (inf->arg)
	{
		inf->argv = strtow(inf->arg, " \t");
		if (!inf->argv)
		{

			inf->argv = malloc(sizeof(char *) * 2);
			if (inf->argv)
			{
				inf->argv[0] = _strdupli(inf->arg);
				inf->argv[1] = NULL;
			}
		}
		for (i = 0; inf->argv && inf->argv[i]; i++)
			;
		inf->argc = i;

		rep_alias(inf);
		rep_vars(inf);
	}
}

/**
 * free_info - frees info_t
 * @info: struct address
 * @eve: true if freeing every fields
 */
void free_info(info_t *info, int eve)
{i
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (eve)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		ffree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}

