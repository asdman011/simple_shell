#include "shell.h"

/**
 * is_command - Checks if afile is executable command.
 * @info: The info structure.
 * @path: Path to  file.
 * Return: 1 if true, 0 otherwise.
 */
int is_command(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
		return (1);
	return (0);
}

/**
 * duplicate_chars - Duplicates chars from the PATH.
 * @pathstr: The PATH.
 * @start: Start index.
 * @stop: Stop index.
 * Return: to a new buffer.
 */
char *duplicate_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_executable_path - Finds the executable path of a command in the PATH string.
 * @info: The info struct.
 * @pathstr: The PATH string.
 * @cmd: The command to find.
 * Return: Full path of the command if found, or NULL.
 */
char *find_executable_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_command(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = duplicate_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_command(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
