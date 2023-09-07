#include "shell.h"
/**
 * get_history_file - gets the hist file
 * @info: param struct
 * Return: allocated string containg hist file
 */

char *get_history_file(info_t *info)
{
	char *b, *d;

	d = _getenv(info, "HOME=");
	if (!d)
		return (NULL);
	b = malloc(sizeof(char) * (_strlen(d) + _strlen(HIST_FILE) + 2));
	if (!b)
		return (NULL);
	b[0] = 0;
	_strcpy(b, d);
	_strcat(b, "/");
	_strcat(b, HIST_FILE);
	return (b);
}
/**
 * write_history - creates a file, or attach to an existing file
 * @info: the param struct
 * Return: Always 1 on success, else -1
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *fname = get_history_file(info);
	list_t *n = NULL;

	if (!fname)
		return (-1);

	fd = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fname);
	if (fd == -1)
		return (-1);
	for (n = info->history; n; n = n->next)
	{
		_putsfd(n->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}
/**
 * read_history - reads hist from file
 * @info: the param struct
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int k, l = 0, lc = 0;
	ssize_t fd, rdl, fs = 0;
	struct stat st;
	char *buf = NULL, *fname = get_history_file(info);

	if (!fname)
		return (0);

	fd = open(fname, O_RDONLY);
	free(fname);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fs = st.st_size;
	if (fs < 2)
		return (0);
	buf = malloc(sizeof(char) * (fs + 1));
	if (!buf)
		return (0);
	rdl = read(fd, buf, fs);
	buf[fs] = 0;
	if (rdl <= 0)
		return (free(buf), 0);
	close(fd);
	for (k = 0; k < fs; k++)
		if (buf[k] == '\n')
		{
			buf[k] = 0;
			build_history_list(info, buf + l, lc++);
			l = k + 1;
		}
	if (l != k)
		build_history_list(info, buf + l, lc++);
	free(buf);
	info->histcount = lc;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}
/**
 * build_history_list - adds entry to a history linked list
 * @info: Struct containing potential args. Used to maintain
 * @buf: buf
 * @linecount: the history linecount, histcount
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *n = NULL;

	if (info->history)
		n = info->history;
	add_node_end(&n, buf, linecount);

	if (!info->history)
		info->history = n;
	return (0);
}
/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Struct consisting potential args Used. 
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	list_t *n = info->history;
	int k = 0;

	while (n)
	{
		n->num = k++;
		n = n->next;
	}
	return (info->histcount = k);
}
