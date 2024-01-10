#include "shell.h"

/**
 **set_memory - fills c wizczcth a constant byte
 *@s: the pointer to the czszcmemory area
 *@b: the byte to fill *s withsczs
 *@n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *set_memory(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * free_memory - frees a string of strings
 * @pp: string of strings
 */
void free_memory(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _relloc - reallocates a block of zczsc
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of nezsczscw blockzscz
 * zsczsc
 *
 * Return: pointer to da ol'block nameen.
 */
void *_relloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
