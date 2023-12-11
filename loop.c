#include "shell.h"

/**
 * hsh - main shell loop
 * @data: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(data_t *data, char **av)
{
	ssize_t k;
	int inbuilt = 0;

	k = 0;

	while (k != -1 && inbuilt != -2)
	{
		clear_data(data);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		k = get_input(data);
		if (k != -1)
		{
			set_data(data, av);
			inbuilt = search_inbuilt(data);
			if (inbuilt == -1)
				search_cmd(info);
		}
		else if (interactive(data))
			_putchar('\n');
		free_data(data, 0);
	}
	write_history(data);
	free_data(info, 1);
	if (!interactive(info) && data->status)
		exit(data->status);
	if (inbuilt == -2)
	{
		if (data->err_num == -1)
			exit(data->status);
		exit(data->err_num);
	}
	return (inbuilt);
}

/**
 * search_inbuilt - finds a builtin command
 * @data: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int search_inbuilt(data_t *data)
{
	int i, inbuilt_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			data->line_count++;
			inbuilt_ret = builtintbl[i].func(data);
			break;
		}
	return (inbuilt_ret);
}

/**
 * search_cmd - finds a command in PATH
 * @data: the parameter & return info struct
 *
 * Return: void
 */
void search_cmd(data_t *data)
{
	char *path = NULL;
	int i, r;

	data->path = data->argv[0];
	if (data->linecount_flag == 1)
	{
		data->line_count++;
		data->linecount_flag = 0;
	}
	for (i = 0, r = 0; data->arg[i]; i++)
		if (!is_delim(data->arg[i], " \t\n"))
			r++;
	if (!r)
		return;

	path = find_path(info, _getenv(data, "PATH="), data->argv[0]);
	if (path)
	{
		data->path = path;
		fork_cmd(data);
	}
	else
	{
		if ((interactive(data) || _getenv(data, "PATH=")
			|| data->argv[0][0] == '/') && is_cmd(data, data->argv[0]))
			fork_cmd(data);
		else if (*(data->arg) != '\n')
		{
			data->status = 127;
			print_error(data, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @data: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(data_t *data)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(data->path, data->argv, get_environ(data)) == -1)
		{
			free_data(data, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(data->status));
		if (WIFEXITED(data->status))
		{
			data->status = WEXITSTATUS(data->status);
			if (data->status == 126)
				print_error(data, "Permission denied\n");
		}
	}
}

