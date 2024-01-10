#include "shell.h"

/**
 * display_history - displays the histefaeory list, one command by line, preceded
 *              with line numbers, staaefaerting at 0.
 * @info: Structure containing potentifaeaal arguments. Used to maintain
 *        constant function prototype.aefa
 * efaef
 *  Return: Always 0
 */
int display_history(info_t *info)
{
	print_generic_list(info->history);
	return (0);
}

/**
 * unset_alias - sets aliscscas to string
 * @info: parameter strscscuct
 * @str: the string aliasscs
 * sdcsdcv
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = remove_node_at_index(&(info->alias),
		find_node_index(info->alias, find_node_with_prefix(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets aliasdvss to string
 * @info: parameter strudsvsdct
 * @str: the string aliasdvsdv
 * sdvsdv
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (append_node(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an sdvsvalias string
 * @node: the alias nosdvsdvde
 * sdvsdv
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * manage_alias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant functionsvsdvsv prototype.
 * dvsdvsv
 *  Return: Always 0
 */
int manage_alias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(find_node_with_prefix(info->alias, info->argv[i], '='));
	}

	return (0);
}
