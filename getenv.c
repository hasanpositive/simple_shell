#include "shell.h"
/**
 * get_environ - returns the str arr copy of our environ
 * @info: Struct of args.
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}
/**
 * _unsetenv - Remove an env var
 * @info: Struct of args.
 * Return: on delete 1, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *n = info->env;
	size_t k = 0;
	char *q;

	if (!n || !var)
		return (0);

	while (n)
	{
		q = starts_with(n->str, var);
		if (q && *q == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), k);
			k = 0;
			n = info->env;
			continue;
		}
		n = n->next;
		k++;
	}
	return (info->env_changed);
}
/**
 * _setenv - Initialize a new env var, or adjust an existing one
 * @info: Struct of args
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *b = NULL;
	list_t *n;
	char *q;

	if (!var || !value)
		return (0);

	b = malloc(_strlen(var) + _strlen(value) + 2);
	if (!b)
		return (1);
	_strcpy(b, var);
	_strcat(b, "=");
	_strcat(b, value);
	n = info->env;
	while (n)
	{
		q = starts_with(n->str, var);
		if (q && *q == '=')
		{
			free(n->str);
			n->str = b;
			info->env_changed = 1;
			return (0);
		}
		n = n->next;
	}
	add_node_end(&(info->env), b, 0);
	free(b);
	info->env_changed = 1;
	return (0);
}
