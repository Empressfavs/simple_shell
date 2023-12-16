#include "shell.h"

/**
 * _memset - A function that fills memory with a constant byte
 * @s: the pointer to the memory area
 * @b: the byte to fill *s with
 * @n: the amount of bytes to be filled
 * Return: (s) a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - A function that frees a string of strings
 * @pp: string of strings
 */
void ffree(char **pp)
{
	char **c = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(c);
}

/**
 * _realloc - A function that reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 * Return: pointer
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char c;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	c = malloc(new_size);
	if (!c)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		c[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (c);
}
