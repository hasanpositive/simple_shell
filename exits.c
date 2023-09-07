#include "shell.h"
/**
 **_strncpy - copies a str
 *@dest: the dest str to be copied to
 *@src: the source str
 *@n: the amount of char to be copied
 *Return: the concat str
 */
char *_strncpy(char *dest, char *src, int n)
{
	int a, b;
	char *d = dest;

	a = 0;
	while (src[a] != '\0' && a < n - 1)
	{
		dest[a] = src[a];
		a++;
	}
	if (a < n)
	{
		b = a;
		while (b < n)
		{
			dest[b] = '\0';
			b++;
		}
	}
	return (d);
}
/**
 **_strncat - concats two strings
 *@dest: the first string to concat
 *@src: the second string to concat
 *@n: the amt of bytes to be used atmost
 *Return: the concated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int b, d;
	char *c = dest;

	b = 0;
	d = 0;
	while (dest[b] != '\0')
		b++;
	while (src[d] != '\0' && d < n)
	{
		dest[b] = src[d];
		b++;
		d++;
	}
	if (d < n)
		dest[b] = '\0';
	return (c);
}
/**
 **_strchr - locates a char in a str
 *@s: the str to be parsed
 *@c: the char to search for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
