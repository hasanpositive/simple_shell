#include "shell.h"

/**
 * _myenv - prints the current env
 * @info: Struct containing potential args. Used to maintain
 * constant func prototype.
 * Return: 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}
/**
 * _getenv - gets the value of an env var
 * @info: Struct consisting potential args. Used to maintain
 * @name: environ var name
 * Return: the value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *n = info->env;
	char *q;

	while (n)
	{
		q = starts_with(n->str, name);
		if (q && *q)
			return (q);
		n = n->next;
	}
	return (NULL);
}
/**
 * _mysetenv - Initialize a new env var,or modify an existing one
 * @info: Struc containing potential args. Used to maintain
 * const func prototype.
 * Return: Always 0
 */
int _mysetenv(info_t *info)
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
 * _myunsetenv - Remove an env var
 * @info: Struct containing potential ars. Used to maintain
 * const func prototype.
 * Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int v;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (v = 1; v <= info->argc; v++)
		_unsetenv(info, info->argv[v]);

	return (0);
}
/**
 * populate_env_list - populates env linked list
 * @info: Struc consisting potential args. Used to maintain
 * const func prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *n = NULL;
	size_t k;

	for (k = 0; environ[k]; k++)
		add_node_end(&n, environ[k], 0);
	info->env = n;
	return (0);
}
