#include "shell.h"

/**
 * count_list_elemsczszents - deterzsczscmines length of linked list
 * @h: pointer to first nodezcszs
 * zsczsc
 *
 * Return: size of list
 */
size_t count_list_elements(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * convert_list_to_strings - retur sczscsz the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **convert_list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = count_list_elements(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_generic_list - s czs all elsczscements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_generic_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * find_node_with_prefix - cz nczzscozscde whoszcsze strzczcing starts with prefix
 * @node: pointer to list hcdxzcead
 * @prefix: string to match
 * @c: the next character after prefix to match
 * dvxdxvx
 *
 * Return: match node or null
 */
list_t *find_node_with_prefix(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * find_node_index - gets dvxv index of a node
 * @head: pointer to list head
 * @node: pointer to the nodexvxvx
 * dxvxv
 *
 * Return: index of node or -1
 */
ssize_t find_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
