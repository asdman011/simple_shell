#include "shell.h"

/**
 * display_history - Display the command history with line numbers.
 *
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int display_history(info_t *info)
{
    /* Print the command history with line numbers */
    print_generic_list(info->history);
    return (0);
}

/**
 * unset_alias - Unset an alias associated with a string.
 *
 * @info: Parameter struct.
 * @str: The string alias.
 * Return: 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *str)
{
    char *equals_sign, saved_char;
    int ret;

    equals_sign = _strchr(str, '=');
    if (!equals_sign)
        return (1);

    saved_char = *equals_sign;
    *equals_sign = '\0';

    /* Remove the alias from the linked list */
    ret = remove_node_at_index(&(info->alias),
                               find_node_index(info->alias,
                                               find_node_with_prefix(info->alias, str, -1)));
    *equals_sign = saved_char;
    return (ret);
}

/**
 * set_alias - Set an alias associated with a string.
 *
 * @info: Parameter struct.
 * @str: The string alias.
 * Return: 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *str)
{
    char *equals_sign;

    equals_sign = _strchr(str, '=');
    if (!equals_sign)
        return (1);

    /* Unset the alias if an empty string is provided */
    if (!*++equals_sign)
        return unset_alias(info, str);

    /* Remove existing alias and append the new one to the linked list */
    unset_alias(info, str);
    return (append_node(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Print an alias string.
 *
 * @node: The alias node.
 * Return: 0 on success, 1 on error.
 */
int print_alias(list_t *node)
{
    char *equals_sign, *alias_start;

    if (node)
    {
        equals_sign = _strchr(node->str, '=');
        alias_start = node->str;

        /* Print the alias and its value */
        while (alias_start <= equals_sign)
            _putchar(*alias_start++);

        _putchar('\'');
        _puts(equals_sign + 1);
        _puts("'\n");

        return (0);
    }

    return (1);
}

/**
 * manage_alias - Mimic the alias builtin (man alias).
 *
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int manage_alias(info_t *info)
{
    int i = 0;
    char *equals_sign;
    list_t *node = NULL;

    /* Display all aliases if no arguments are provided */
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

    /* Process each argument provided */
    for (i = 1; info->argv[i]; i++)
    {
        equals_sign = _strchr(info->argv[i], '=');

        /* Set or unset alias based on the presence of '=' in the argument */
        if (equals_sign)
            set_alias(info, info->argv[i]);
        else
            print_alias(find_node_with_prefix(info->alias, info->argv[i], '='));
    }

    return (0);
}
