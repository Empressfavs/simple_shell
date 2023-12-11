#include "shell.h"

/**
 * err_atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string otherwise -1 on error
 */
int err_atoi(char *s)
{
	int l = 0;
	unsigned long int res = 0;

	if (*s == '+')
		s++;
	for (l = 0;  s[l] != '\0'; l++)
	{
		if (s[l] >= '0' && s[l] <= '9')
		{
			res *= 10;
			res += (s[l] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * print_error - prints an error message
 * @inf: the parameter & return info struct
 * @errstr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void display_err(info_t *inf, char *errstr)
{
	_eputs(inf->fname);
	_eputs(": ");
	print_d(inf->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(inf->argv[0]);
	_eputs(": ");
	_eputs(errstr);
}

/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @f: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int display_p(int input, int f)
{
	int (*__putchar)(char) = _putchar;
	int l, len = 0;
	unsigned int _abs_, new;

	if (f == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		len++;
	}
	else
		_abs_ = input;
	new = _abs_;
	for (l = 1000000000; l > 1; l /= 10)
	{
		if (_abs_ / l)
		{
			__putchar('0' + new / l);
			len++;
		}
		new %= l;
	}
	__putchar('0' + new);
	len++;

	return (len);
}

/**
 * convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_num(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void rem_comments(char *buf)
{
	int l;

	for (l = 0; buf[l] != '\0'; l++)
		if (buf[l] == '#' && (!l || buf[l - 1] == ' '))
		{
			buf[l] = '\0';
			break;
		}
}

