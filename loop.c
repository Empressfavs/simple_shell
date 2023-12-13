#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @arv: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **arv)
{
	ssize_t t = 0;
	int b = 0;

	while (t != -1 && b != -2)
	{
		clear_inf(info);
		if (interact(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		t = _input(info);
		if (t != -1)
		{
			set_inf(info, arv);
			b = find_builtin(info);
			if (b == -1)
				find_cmd(info);
		}
		else if (interact(info))
			_putchar('\n');
		free_info(info, 0);
	}
	create_history(info);
	free_info(info, 1);
	if (!interact(info) && info->status)
		exit(info->status);
	if (b == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (b);
}

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 * Return: -1 if builtin not found, 0 if successful, 1 not successful, -2 if signal exit
 */
int find_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _ourexit},
		{"env", _environment},
		{"help", _chcur},
		{"history", _history},
		{"setenv", _setenviron},
		{"unsetenv", _unsetenviron},
		{"cd", _ourcd},
		{"alias", _alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_str_cmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_del(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info, _environment(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interact(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_command(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

