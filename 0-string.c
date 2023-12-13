#include "shell.h"

/**
 * _str_len - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int _str_len(char *s)
{
	int j = 0;

	if (!s)
		return (0);

	while (*s++)
		j++;
	return (j);
}

/**
 * _str_cmp - performs lexicogarphic comparison of two strangs.
 * @str1: the first strang
 * @str2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _str_cmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with ser
 * @ser: string to search
 * @fin: the substring to find
 * Return: address of next char of ser or NULL
 */
char *starts_with(const char *ser, const char *fin)
{
	while (*fin)
		if (*fin++ != *ser++)
			return (NULL);
	return ((char *)ser);
}

/**
 * _str_cat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 * Return: pointer to destination buffer
 */
char *_str_cat(char *dest, char *src)
{
	char *p = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (p);
}

