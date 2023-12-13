#include "shell.h"

/**
 **_memset - fills memory with a constant byte
 *@s: the pointer to the memory area
 *@b: the byte to fill *s with
 *@n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * _free - frees a string of strings
 * @ss: string of strings
 */
void _free(char **ss)
{
	char **c = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(c);
}

/**
 * _reallocate - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_reallocate(void *ptr, unsigned int prev_size, unsigned int new_size)
{
	char *c;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == prev_size)
		return (ptr);

	c = malloc(new_size);
	if (!c)
		return (NULL);

	prev_size = prev_size < new_size ? prev_size : new_size;
	while (prev_size--)
		c[prev_size] = ((char *)ptr)[prev_size];
	free(ptr);
	return (c);
}

