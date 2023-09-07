#include "shell.h"
/**
 **_memset - fills memory with a constant byte
 *@s: the pointer to area of the memory
 *@b: the byte to fill *s with
 *@n: the amt of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int a;

	for (a = 0; a < n; a++)
		s[a] = b;
	return (s);
}
/**
 * ffree - frees a string of strs
 * @pp: string of strs
 */
void ffree(char **pp)
{
	char **q = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(q);
}
/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to prev mallocated block
 * @old_size: byte size of prev block
 * @new_size: byte size of new block
 * Return: pointer to the al block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *q;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	q = malloc(new_size);
	if (!q)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		q[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (q);
}
