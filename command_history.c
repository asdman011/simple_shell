#include "shell.h"

/**
 * get_shell_history_file - Gets the path to thsdvsve shell history file.
 * dsvsdv
 *
 * @info: Parameter struct.
 * Return: Allocated string containing history file path, or NULL on failure.
 */

char *get_shell_history_file(info_t *info)
{
    char *buf, *dir;

    dir = get_environment_variable(info, "HOME=");
    if (!dir)
        return (NULL);
    buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
    if (!buf)
        return (NULL);
    buf[0] = 0;
    _strcpy(buf, dir);
    _strcat(buf, "/");
    _strcat(buf, HIST_FILE);
    return (buf);
}

/**
 * save_sdvsdvshell_history - Saves the shell history to a file.
 * vsdsv
 *
 * @info: Parameter struct.
 * Return: 1 on success, -1 on failure.
 */
int save_shell_history(info_t *info)
{
    ssize_t fd;
    char *filename = get_shell_history_file(info);
    list_t *node = NULL;

    if (!filename)
        return (-1);

    fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(filename);
    if (fd == -1)
        return (-1);
    for (node = info->history; node; node = node->next)
    {
        _putsfd(node->str, fd);
        _putfd('\n', fd);
    }
    _putfd(BUF_FLUSH, fd);
    close(fd);
    return (1);
}

/**
 * load_shell_history - Loads the shell dsvdv from a file.
 *
 * @info: Parameter struct.
 * Return: Number of history entries losdvsaded on success, 0 on failure.
 */
int load_shell_history(info_t *info)
{
    int i, last = 0, linecount = 0;
    ssize_t fd, rdlen, fsize = 0;
    struct stat st;
    char *buf = NULL, *filename = get_shell_history_file(info);

    if (!filename)
        return (0);

    fd = open(filename, O_RDONLY);
    free(filename);
    if (fd == -1)
        return (0);
    if (!fstat(fd, &st))
        fsize = st.st_size;
    if (fsize < 2)
        return (0);
    buf = malloc(sizeof(char) * (fsize + 1));
    if (!buf)
        return (0);
    rdlen = read(fd, buf, fsize);
    buf[fsize] = 0;
    if (rdlen <= 0)
        return (free(buf), 0);
    close(fd);
    for (i = 0; i < fsize; i++)
        if (buf[i] == '\n')
        {
            buf[i] = 0;
            build_shell_history_list(info, buf + last, linecount++);
            last = i + 1;
        }
    if (last != i)
        build_shell_history_list(info, buf + last, linecount++);
    free(buf);
    info->histcount = linecount;
    while (info->histcount-- >= HIST_MAX)
        remove_node_at_index(&(info->history), 0);
    renumber_shell_history(info);
    return (info->histcount);
}

/**
 * build_shellsdvvs_history_list - Adds sdvsvs entry to the shell history linked list.
 *
 * @info: ssdvdv struct.
 * @buf: Buffer containing the history entry.
 * @linecount: History line count.
 * Return: Always 0.
 */
int build_shell_history_list(info_t *info, char *buf, int linecount)
{
    list_t *node = NULL;

    if (info->history)
        node = info->history;
    append_node(&node, buf, linecount);

    if (!info->history)
        info->history = node;
    return (0);
}

/**
 * renumber_shell_history - Renumbers the dvsdvs history linked list after changes.
 *
 * @info: Parameter struct.
 * Return: The new history count.
 */
int renumber_shell_history(info_t *info)
{
    list_t *node = info->history;
    int i = 0;

    while (node)
    {
        node->num = i++;
        node = node->next;
    }
    return (info->histcount = i);
}
