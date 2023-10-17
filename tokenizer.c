#include "shell.h"
/**
 * **strtow - splits a string into words.
 * @str: the input string
 * @d: the delim string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int a, b, c, f, nw = 0;
	char **g;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!is_delim(str[a], d) && (is_delim(str[a + 1], d) || !str[a + 1]))
			nw++;

	if (nw == 0)
		return (NULL);
	g = malloc((1 + nw) * sizeof(char *));
	if (!g)
		return (NULL);
	for (a = 0, b = 0; b < nw; b++)
	{
		while (is_delim(str[a], d))
			a++;
		c = 0;
		while (!is_delim(str[a + c], d) && str[a + c])
			c++;
		g[b] = malloc((c + 1) * sizeof(char));
		if (!g[b])
		{
			for (c = 0; c < b; c++)
				free(g[c]);
			free(g);
			return (NULL);
		}
		for (f = 0; f < c; f++)
			g[b][f] = str[a++];
		g[b][f] = 0;
	}
	g[b] = NULL;
	return (g);
}
/**
 * **strtow2 -divide a string into words
 * @str: the input string
 * @d: the delim
 * Return: a pointer to an arr of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int a, b, c, f, nw = 0;
	char **g;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != d && str[a + 1] == d) ||
		    (str[a] != d && !str[a + 1]) || str[a + 1] == d)
			nw++;
	if (nw == 0)
		return (NULL);
	g = malloc((1 + nw) * sizeof(char *));
	if (!g)
		return (NULL);
	for (a = 0, b = 0; b < nw; b++)
	{
		while (str[a] == d && str[a] != d)
			a++;
		c = 0;
		while (str[a + c] != d && str[a + c] && str[a + c] != d)
			c++;
		g[b] = malloc((c + 1) * sizeof(char));
		if (!g[b])
		{
			for (c = 0; c < b; c++)
				free(g[c]);
			free(g);
			return (NULL);
		}
		for (f = 0; f < c; f++)
			g[b][f] = str[a++];
		g[b][f] = 0;
	}
	g[b] = NULL;
	return (g);
}
