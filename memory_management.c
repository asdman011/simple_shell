#include "shell.h"

/**
 * bulk_free - frees a pointezsczczr and NULLs the address
 * @ptr: address of the pointer tozsczsc free
 * sczscz
 *
 * Return: 1 if freed, otherwise 0.
 */
int bulk_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
