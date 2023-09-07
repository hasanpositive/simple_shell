#include "shell.h"
/**
 * list_len - determines length of linked list
 * @h: first node pointer
 * Return: size of list
 */
size_t list_len(const list_t *h)
{
	size_t v = 0;

	while (h)
	{
		h = h->next;
		v++;
	}
	return (v);
}
/**
 * list_to_strings - returns an arr of sts of the list->str
 * @head: pointer to first node
 * Return: arr of strs
 */
char **list_to_strings(list_t *head)
{
	list_t *n = head;
	size_t k = list_len(head), m;
	char **strs;
	char *str;

	if (!head || !k)
		return (NULL);
	strs = malloc(sizeof(char *) * (k + 1));
	if (!strs)
		return (NULL);
	for (k = 0; n; n = n->next, k++)
	{
		str = malloc(_strlen(n->str) + 1);
		if (!str)
		{
			for (m = 0; m < k; m++)
				free(strs[m]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, n->str);
		strs[k] = str;
	}
	strs[k] = NULL;
	return (strs);
}
/**
 * print_list - prints all elements of a list_t linked list
 * @h: the pointer to first node
 * Return: the size of list
 */
size_t print_list(const list_t *h)
{
	size_t k = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		k++;
	}
	return (k);
}
/**
 * node_starts_with - returns node whose str starts with prefix
 * @node: the pointer to list head
 * @prefix the str to match
 * @c: the next char after prefix to match
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *pr = NULL;

	while (node)
	{
		pr = starts_with(node->str, prefix);
		if (pr && ((c == -1) || (*pr == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}
/**
 * get_node_index - gets the index of a node
 * @head: the pointer to list head
 * @node: the pointer to the node
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t k = 0;

	while (head)
	{
		if (head == node)
			return (k);
		head = head->next;
		k++;
	}
	return (-1);
}
