#include "shell.h"

/**
 * input_buf - buffers chaizsczscned commands
 * @info: parameter strczscszuct
 * @buf: address of buffer
 * @len: address of lenzsczsc var
 * sczsc
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bulk_free((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, handle_interrupt_signal);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = get_line(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_shell_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * read_input - gets a line zcs the newline
 * @info: parametzczscer struct
 *
 * Return: bytes read
 */
ssize_t read_input(info_t *info)
{
	static char *buf; /* the ';' zcsz chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)	/* we have zsczs left in the chain buffer */
	{
		j = i; /* init new zsczsc to current buf position */
		p = buf + i; /* get zscz for return */

		inspect_var_chain(info, buf, &j, i, len);
		while (j < len) /* zscs to semicolon or end */
		{
			if (is_var_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* zscszc past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to dcdxc command position */
		return (_strlen(p)); /* return lengtccch of current command */
	}

	*buf_p = buf; /* else not a chain, cccpass back buffer from get_line() */
	return (r); /* return length ofccc buffer from get_line() */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * get_line - gets the next line of xvvinpuvdxvt from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to dvxvbuffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int get_line(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _relloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * handle_interrupt_signal -czsc blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void handle_interrupt_signal(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
