#include "shell.h"
/**
 * _myhistory - disp the history list, one cmd by line, further
 * with line numbers, starting at 0.
 * @info: Struct consisting potential args. Used to maintain
 * constant func prototype.
 * Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}
/**
 * unset_alias - sets alias to string
 * @info: param struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *a, s;
	int r;

	a = _strchr(str, '=');
	if (!a)
		return (1);
	s = *a;
	*a = 0;
	r = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*a = s;
	return (r);
}

/**
 * set_alias - sets alias to string
 * @info: param struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *s;

	s = _strchr(str, '=');
	if (!s)
		return (1);
	if (!*++s)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}
/**
 * print_alias - prints an alias string
 * @node: the alias node
 * Return: 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *n = NULL, *c = NULL;

	if (node)
	{
		n = _strchr(node->str, '=');
		for (c = node->str; c <= n; c++)
			_putchar(*c);
		_putchar('\'');
		_puts(n + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
/**
 * _myalias - act like the alias builtin (man alias)
 * @info: Struct containing potential args. Used to maintain
 * constant function prototype.
 * Return: 0 Always
 */
int _myalias(info_t *info)
{
	int k = 0;
	char *c = NULL;
	list_t *n = NULL;

	if (info->argc == 1)
	{
		n = info->alias;
		while (n)
		{
			print_alias(n);
			n = n->next;
		}
		return (0);
	}
	for (k = 1; info->argv[k]; k++)
	{
		c = _strchr(info->argv[k], '=');
		if (c)
			set_alias(info, info->argv[k]);
		else
			print_alias(node_starts_with(info->alias, info->argv[k], '='));
	}

	return (0);
}
