#include "shell.h"

/**
 * _ourexit - exits the shell
 * @data: Contains potential arguments used to maintain constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _ourexit(info_t *data)
{
	int exitcheck;

	if (data->argv[1])
	{
		exitcheck = _errtrum(data->argv[1]);
		if (exitcheck == -1)
		{
			data->status = 2;
			print_error(data, "Invalid number: ");
			_eputs(data->argv[1]);
			_eputchar('\n');
			return (1);
		}
		data->err_num = _errtrum(data->argv[1]);
		return (-2);
	}
	data->err_num = -1;
	return (-2);
}

/**
 * _ourcd - change the current directory of the process
 * @data: Contains potential arguments used to maintain constant function prototype.
 *  Return: Always 0
 */
int _ourcd(info_t *data)
{
	char *c, *direct, buffer[1024];
	int ch_dir;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!data->argv[1])
	{
		direct = _getenv(data, "HOME=");
		if (!direct)
			ch_dir = chdir((direct = _getenv(data, "PWD=")) ? direct : "/");
		else
			ch_dir = chdir(direct);
	}
	else if (_strcmp(data->argv[1], "-") == 0)
	{
		if (!_getenv(data, "OLDPWD="))
		{
			_puts(s);
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
 * _chcur - changes the current directory of the process
 * @data: Contains potential arguments used to maintain constant function prototype.
 *  Return: Always 0
 */
int _chcur(info_t *data)
{
	char **arg_array;

	arg_array = data->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
