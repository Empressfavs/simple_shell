#include "shell.h"

/**
 * _exit - exits the shell
 * @data: contains arguments. Used to maintain constant function prototype.
 *  Return: exits with a given exit status
 */
int _exit(data_t *data)
{
	int checkexit;

	if (data->argv[1])
	{
		checkexit = _errtrum(data->argv[1]);
		if (checkexit == -1)
		{
			data->status = 2;
			print_err(data, "Invalid number: ");
			_eputs(data->argv[1]);
			_eputchar('\n');
			return (1);
		}
		data->error_num = _errtrum(data->argv[1]);
		return (-2);
	}
	data->error_num = -1;
	return (-2);
}

/**
 * _cd - changes the current directory
 * @data: contains arguments used to maintain constant function prototype.
 *  Return: Always 0
 */
int _cd(data_t *data)
{
	char *c, *direct, buffer[1024];
	int ch_dir;

	c = getcwd(buffer, 1024);
	if (!c)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!data->argv[1])
	{
		direct = _getenv(data, "HOME=");
		if (!direct)
			ch_dir = chdir((direct = _getenv(info, "PWD=")) ? direct : "/");
		else
			ch_dir = chdir(direct);
	}
	else if (_strcmp(data->argv[1], "-") == 0)
	{
		if (!_getenv(data, "OLDPWD="))
		{
			_puts(c);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(data, "OLDPWD=")), _putchar('\n');
		ch_dir = chdir((direct = _getenv(data, "OLDPWD=")) ? direct : "/");
	}
	else
		ch_dir = chdir(data->argv[1]);
	if (ch_dir == -1)
	{
		print_error(data, "can't cd to ");
		_eputs(data->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(data, "OLDPWD", _getenv(data, "PWD="));
		_setenv(data, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _current - changes the current directory
 * @data: Contain arguments used to maintain constant function prototype.
 *  Return: Always 0
 */
int _current(data_t *data)
{
	char **arg_arr;

	arg_arr = data->argv;
	_puts("Function not yet implemented \n");
	if (0)
		_puts(*arg_arr);
	return (0);
}
