#include "shell.h"
/**
 * _erratoi - conv a str to an int
 * @s: the str to be conv
 * Return: if no num in string 0, conv num otherwise -1 on err
 */
int _erratoi(char *s)
{
	int w = 0;
	unsigned long int res = 0;

	if (*s == '+')
		s++;
	for (w = 0;  s[w] != '\0'; w++)
	{
		if (s[w] >= '0' && s[w] <= '9')
		{
			res *= 10;
			res += (s[w] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}
/**
 * print_error - prints an err msg
 * @info: return info struct and param
 * @estr: str consisting specified err type
 * Return: if no num in string 0, conv num otherwise -1 on err
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}
/**
 * print_d - func prints a decimal (int) num (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 * Return: num of char printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int k, c = 0;
	unsigned int absolute, cur;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		absolute = -input;
		__putchar('-');
		c++;
	}
	else
		absolute = input;
	cur = absolute;
	for (k = 1000000000; k > 1; k /= 10)
	{
		if (absolute / k)
		{
			__putchar('0' + cur / k);
			c++;
		}
		cur %= k;
	}
	__putchar('0' + cur);
	c++;

	return (c);
}
/**
 * convert_number - conv func, a clone of itoa
 * @num: number
 * @base: base
 * @flags: arg flags
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *arr;
	static char buffer[50];
	char s = 0;
	char *p;
	unsigned long numb = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		numb = -num;
		s = '-';

	}
	arr = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buffer[49];
	*p = '\0';

	do	{
		*--p = arr[numb % base];
		numb /= base;
	} while (numb != 0);

	if (s)
		*--p = s;
	return (p);
}
/**
 * remove_comments - func replaces first instance of '#' with '\0'
 * @buf: address of the string to adjust
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int z;

	for (z = 0; buf[z] != '\0'; z++)
		if (buf[z] == '#' && (!z || buf[z - 1] == ' '))
		{
			buf[z] = '\0';
			break;
		}
}
