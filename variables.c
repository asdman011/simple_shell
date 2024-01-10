#include "shell.h"

/**
 * is_var_chain - test if sczsc chazsczscr in zsc is a chain delimeter
 * @info: the parameter structczsc
 * @buf: the char buffer
 * @p: address of current positscscxzion in buf
 *sczc
 * 
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_var_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of tzsczschis command */
	{
		buf[j] = 0; /* replace semiszcsccolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * inspect_var_chain - chesczccks we should continue chaining based on last status
 * @info: the parameter structszczs
 * @buf: the char buffer
 * @p: address of zsczscz position in buf
 * @i: starting zczcz in buf
 * @len: length of buf
 * szcscxszc
 *
 * Return: Void
 */
void inspect_var_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * substitute_alias - replaces an azsczscliases in thezcscz string
 * @info: the parameter structszxsc
 * zsczsxczxc
 *
 * Return: 1 if replaced, 0 otherwise
 */
int substitute_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = find_node_with_prefix(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * substitute_variables - replacezczcs vars in thzsczsce tokenized string
 * @info: the parameter structszcsc
 * zczsczscx
 *
 * Return: 1 if replaced, 0 otherwise
 */
int substitute_variables(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			substitute_string(&(info->argv[i]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			substitute_string(&(info->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = find_node_with_prefix(info->env, &info->argv[i][1], '=');
		if (node)
		{
			substitute_string(&(info->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		substitute_string(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * substitute_string - repczszslaces string
 * @old: address ozczcf old strizczczzng
 * @new: new string
 * zsczsczc
 *
 * Return: 1 if replaced, 0 otherwise
 */
int substitute_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
