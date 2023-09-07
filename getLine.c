#include "shell.h"
/**
 * input_buf - buf chained cmds
 * @info: struct param
 * @buf: address of buf
 * @len: address of len var
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t k = 0;
	size_t p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		k = getline(buf, &p, stdin);
#else
		k = _getline(info, buf, &p);
#endif
		if (k > 0)
		{
			if ((*buf)[k - 1] == '\n')
			{
				(*buf)[k - 1] = '\0';
				k--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = k;
				info->cmd_buf = buf;
			}
		}
	}
	return (k);
}
/**
 * get_input - gets a line without the newline
 * @info: parameter struct
 * Return: read bytes
 */
ssize_t get_input(info_t *info)
{
	static char *bf;
	static size_t a, b, c;
	ssize_t d = 0;
	char **buf_p = &(info->arg), *q;

	_putchar(BUF_FLUSH);
	d = input_buf(info, &bf, &c);
	if (d == -1)
		return (-1);
	if (c)
	{
		b = a;
		q = bf + a;

		check_chain(info, bf, &b, a, c);
		while (b < c)
		{
			if (is_chain(info, bf, &b))
				break;
			b++;
		}

		a = b + 1; 
		if (a >= c)
		{
			a = c = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = q;
		return (_strlen(q));
	}

	*buf_p = bf;
	return (d);
}
/**
 * read_buf - reads a buffer
 * @info: struct param
 * @buf: buf
 * @i: size
 * Return: ret
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t ret = 0;

	if (*i)
		return (0);
	ret = read(info->readfd, buf, READ_BUF_SIZE);
	if (ret >= 0)
		*i = ret;
	return (ret);
}
/**
 * _getline - gets the next line of input from STDIN
 * @info: struct Param
 * @ptr: address of pointer to buf, preallocated or NULL
 * @length: size of preallocated ptr buf if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t a, l;
	size_t d;
	ssize_t f = 0, s = 0;
	char *b = NULL, *new_b = NULL, *c;

	b = *ptr;
	if (b && length)
		s = *length;
	if (a == l)
		a = l = 0;

	f = read_buf(info, buf, &l);
	if (f == -1 || (f == 0 && l == 0))
		return (-1);

	c = _strchr(buf + a, '\n');
	d = c ? 1 + (unsigned int)(c - buf) : l;
	new_b = _realloc(b, s, s ? s + d : d + 1);
	if (!new_b)
		return (b ? free(b), -1 : -1);

	if (s)
		_strncat(new_b, buf + a, d - a);
	else
		_strncpy(new_b, buf + a, d - a + 1);

	s += d - a;
	a = d;
	b = new_b;

	if (length)
		*length = s;
	*ptr = b;
	return (s);
}
/**
 * sigintHandler - ctrl-C blocks
 * @sig_num: the signal number
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
