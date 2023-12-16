#include "shell.h"
/**
 * interactive - A function that returns true if shell is interactive mode
 * @info: struct address
 * Return: 1 if interactive mode, or 0 if not
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - A function that checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - A function that checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - A function that converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int i, sign = 1, tag = 0, output;
	unsigned int outcome = 0;

	for (i = 0; s[i] != '\0' && tag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			tag = 1;
			outcome *= 10;
			outcome += (s[i] - '0');
		}
		else if (tag == 1)
			tag = 2;
	}

	if (sign == -1)
		output = -outcome;
	else
		output = outcome;

	return (output);
}
