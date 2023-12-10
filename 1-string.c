#include "shell.h"

/**
 * _str_cpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_str_cpy(char *dest, char *src)
{
	int j = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[j])
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = 0;
	return (dest);
}

/**
 * _str_dupli - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdupli(const char *str)
{
	int len;
	char *p;

	len = 0;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	p = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	for (len++; len--;)
		p[len] = *--str;
	return (p);
}

/**
 *_puts - prints an input string
 *@str: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		_putchar(str[j]);
		j++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char char)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (char == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(1, buf, j);
		j = 0;
	}
	if (char != BUF_FLUSH)
		buf[j++] = char;
	return (1);
}
