#include "shell.h"

/**
 * display_environment - prints the current environment
 * aesdfA
 * @info: Structure containing potential arguments. Used to maintain
 *constant function prototype.
 * Return: Always 0
 */
int display_environment(info_t *info)
{
	print_string_list(info->env);
	return (0);
}

/**
 * get_environment_variable - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *SDVD\S
 * Return: the value
 */
char *get_environment_variable(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * set_environment_variable - Initialize a new environment variable,
 *or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *constant function prototype.
 *  Return: Always 0
 */
int set_environment_variable(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * unset_environment_variable - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * IUconstant function prototype.
 *  Return: Always 0
 */
int unset_environment_variable(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_ls - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 * H constant function prototype.
 * Return: Always 0
 */
int populate_env_ls(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		append_node(&node, environ[i], 0);
	info->env = node;
	return (0);
}
