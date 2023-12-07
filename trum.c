#include "shell.h"

/**
 * conn - returns true if shell is interactive mode
 * @data: struct address
 *
 * Return: 1 if interactive mode or 0 if not
 */
int conn(data_t *data)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delimiter - checks if it is a delimeter
 * @c: the character to check
 * @delimiter: the delimeter string
 * Return: 1 if it is true or 0 if not
 */
int is_delimiter(char c, char *delimiter)
{
	while (*delimiter)
		if (*delimiter++ == c)
			return (1);
	return (0);
}

/**
 *_alphabet - checks for alphabets
 *@c: The character to input
 *Return: 1 if c is is an alphabet or 0 if not
 */

int _alphabet(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_trum - converts a string to an integer
 *@s: the string converted
 *Return: 0 if no numbers in string
 */

int _trum(char *s)
{
	int i, fig = 1, stan = 0, output;
	unsigned int product = 0;

	for (i = 0;  s[i] != '\0' && stan != 2; i++)
	{
		if (s[i] == '-')
			fig *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			stan = 1;
			product *= 10;
			product += (s[i] - '0');
		}
		else if (stan == 1)
			stan = 2;
	}

	if (fig == -1)
		output = -product;
	else
		output = product;

	return (output);
}

