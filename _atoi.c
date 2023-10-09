#include "shell.h"
/**
 * interactive - produce true
 * @info: struct address
 * Return: if interactive mode 1, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks char
 * @c: the char to check
 * @delim: the delim string
 * Return: if true 1, 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}
/**
 * _isalpha - checks for alpha char
 * @c: The char as input
 * Return: if c is alpha 1, 0 otherwise
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
/**
 * _atoi - converts a string
 * @s: the converted string
 * Return: if no num in string 0, converted num otherwise
 */
int _atoi(char *s)
{
	int k, sn = 1, fg = 0, out;
	unsigned int r = 0;

	for (k = 0; s[k] != '\0' && fg != 2; k++)
	{
		if (s[k] == '-')
			sn *= -1;

		if (s[k] >= '0' && s[k] <= '9')
		{
			fg = 1;
			r *= 10;
			r += (s[k] - '0');
		}
		else if (fg == 1)
			fg = 2;
	}

	if (sn == -1)
		out = -r;
	else
		out = r;

	return (out);
}
