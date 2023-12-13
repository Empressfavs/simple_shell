#include "shell.h"

/**
 * interact - returns true if shell is interactive mode
 * @data: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interact(info_t *data)
{
	return (isatty(STDIN_FILENO) && data->readfd <= 2);
}

/**
 * is_del - checks if character is a delimeter
 * @c: the char to check
 * @del: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_del(char c, char *del)
{
	while (*del)
		if (*del++ == c)
			return (1);
	return (0);
}

/**
 *_isalpha - checks if the character is an alphabet
 *@c: The character to input
 *Return: 1 if c is an alphabet or 0 if not
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_trum - converts a string to an integer
 *@d: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _trum(char *d)
{
	int i, sug = 1, tag = 0, output;
	unsigned int outcome = 0;

	for (i = 0;  d[i] != '\0' && tag != 2; i++)
	{
		if (d[i] == '-')
			sug *= -1;

		if (d[i] >= '0' && d[i] <= '9')
		{
			tag = 1;
			outcome *= 10;
			outcome += (d[i] - '0');
		}
		else if (tag == 1)
			tag = 2;
	}

	if (sug == -1)
		output = -outcome;
	else
		output = outcome;

	return (output);
}

