#include "shell.h"

/**
 * _ourexit - exits the shell
 * @info: Contains potential arguments used to maintain function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _ourexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])
	{
		exitcheck = err_atoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			display_err(info, "Invalid number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = err_atoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _ourcd - change the current directory of the process
 * @info: Contains potential arguments used to maintain constant prototype.
 *  Return: Always 0
 */
int _ourcd(info_t *info)
{
	char *c, *direct, buffer[1024];
	int ch_dir;

	c = getcwd(buffer, 1024);
	if (!c)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		direct = _getenviron(info, "HOME=");
		if (!direct)
			ch_dir = chdir((direct = _getenviron(info, "PWD=")) ? direct : "/");
		else
			ch_dir = chdir(direct);
	}
	else if (_str_cmp(info->argv[1], "-") == 0)
	{
		if (!_getenviron(info, "OLDPWD="))
		{
			_puts(c);
			_putchar('\n');
			return (1);
		}
		_puts(_getenviron(info, "OLDPWD=")), _putchar('\n');
		ch_dir = chdir((direct = _getenviron(info, "OLDPWD=")) ? direct : "/");
	}
	else
		ch_dir = chdir(info->argv[1]);
	if (ch_dir == -1)
	{
		display_err(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenviron(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _chcur - changes the current directory of the process
 * @info: Contains potential arguments used to maintain constant prototype.
 *  Return: Always 0
 */
int _chcur(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
