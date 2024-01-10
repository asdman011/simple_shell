#include "shell.h"

/**
 * hsh - Main shell loop function.
 *
 * @info: Parameter & return info struct.
 * @av: Argument vector from main().
 *
 * Return: 0 on success, 1 on error, or error code.
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_sh_info(info);
		if (interactive_mode(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = read_input(info);
		if (r != -1)
		{
			set_sh_info(info, av);
			builtin_ret = find_builtin_command(info);
			if (builtin_ret == -1)
				locate_cmd(info);
		}
		else if (interactive_mode(info))
			_putchar('\n');
		free_sh_info(info, 0);
	}
	save_shell_history(info);
	free_sh_info(info, 1);
	if (!interactive_mode(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin_command - Finds a builtin command in the shell.
 *
 * @info: Parameter & return info struct.
 *
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not successful,
 *        -2 if builtin signals exit().
 */
int find_builtin_command(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", exit_shell},
		{"env", display_environment},
		{"help", display_help},
		{"history", display_history},
		{"setenv", set_environment_variable},
		{"unsetenv", unset_environment_variable},
		{"cd", change_directory},
		{"alias", manage_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * locate_cmd - Locates a command in the PATH.
 *
 * @info: Parameter & return info struct.
 *
 * Return: void.
 */
void locate_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delimiter(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_executable_path(info, get_environment_variable(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		execute_command(info);
	}
	else
	{
		if ((interactive_mode(info) || get_environment_variable(info, "PATH=")
			|| info->argv[0][0] == '/') && is_command(info, info->argv[0]))
			execute_command(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * execute_command - Forks an exec thread to run a command.
 *
 * @info: Parameter & return info struct.
 *
 * Return: void.
 */
void execute_command(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environment_variables(info)) == -1)
		{
			free_sh_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
