#include "shell.h"

/**
* _putchar - writes the character c to stdout
* @c: The character to print
* Return: On success 1.
* On error, -1 is returned and errno set appropriately
*/
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
* print_str - prints a string
* @p: string to be printed
*
* Return: number of characters printed
*/
int print_str(char *p)
{
	int i = 0;

	while (p[i] != '\0')
	{
		_putchar(p[i]);
		i++;
	}

	return (i);
}
