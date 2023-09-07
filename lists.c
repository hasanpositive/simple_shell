#include "shell.h"
/**
 * add_node - adds a node to the start of the list
 * @head: head node's address ptr
 * @str: str node field
 * @num: node index used by hist
 * Return: size of list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}
/**
 * add_node_end - adds a node to the end of the list
 * @head: head node's pointer address
 * @str: str node field
 * @num: node index used by hist
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_n, *n;

	if (!head)
		return (NULL);

	n = *head;
	new_n = malloc(sizeof(list_t));
	if (!new_n)
		return (NULL);
	_memset((void *)new_n, 0, sizeof(list_t));
	new_n->num = num;
	if (str)
	{
		new_n->str = _strdup(str);
		if (!new_n->str)
		{
			free(new_n);
			return (NULL);
		}
	}
	if (n)
	{
		while (n->next)
			n = n->next;
		n->next = new_n;
	}
	else
		*head = new_n;
	return (new_n);
}
/**
 * print_list_str - prints only the str element of a list_t linked list
 * @h: the ptr to first node
 * Return: the size of list
 */
size_t print_list_str(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		a++;
	}
	return (a);
}
/**
 * delete_node_at_index - del node at a given index
 * @head: first node's address pointer 
 * @index: index of node to del
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *n, *p_node;
	unsigned int k = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		n = *head;
		*head = (*head)->next;
		free(n->str);
		free(n);
		return (1);
	}
	n = *head;
	while (n)
	{
		if (k == index)
		{
			p_node->next = n->next;
			free(n->str);
			free(n);
			return (1);
		}
		k++;
		p_node = n;
		n = n->next;
	}
	return (0);
}
/**
 * free_list - frees all nodes of a list
 * @head_ptr: pointer to head node address
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *n, *n_node, *h;

	if (!head_ptr || !*head_ptr)
		return;
	h = *head_ptr;
	n = h;
	while (n)
	{
		n_node = n->next;
		free(n->str);
		free(n);
		n = n_node;
	}
	*head_ptr = NULL;
}
