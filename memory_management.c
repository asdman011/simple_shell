#include "shell.h"

/**
 * bulk_free - frees a ioio and NULLs the address
 * @ptr: address of the pointer to freemlpj
 * joohj
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
