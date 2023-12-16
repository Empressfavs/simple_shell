#include "shell.h"
/**
 * _strcpy - A function that copies a string
 * @dest: the destination
 * @src: the source
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _strdup - A function that duplicates a string
 * @str: the string to duplicate
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int len = 0;
	char *uns;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	uns = malloc(sizeof(char) * (len + 1));
	if (!uns)
		return (NULL);
	for (len++; len--;)
		uns[len] = *--str;
	return (uns);
}

/**
 * _puts - A function that prints an input string
 * @str: the string to be printed
 * Return: Nothing
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - A function that writes the character c to stdout
 * @c: The character to print
 * Return: On success 1 otherwise 0 on error
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
