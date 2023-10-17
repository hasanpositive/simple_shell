#include "shell.h"
/**
 * _myexit - exits the shell
 * @info: Struct containing potential args. 
 * Return: exits with exit status (0)
 * if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int ec;

	if (info->argv[1])
	{
		ec = _erratoi(info->argv[1]);
		if (ec == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}
/**
 * _mycd - changes the current dir
 * @info: Struct which include potential args.
 *  Return: Always 0
 */
int _mycd(info_t *info)
{
	char *p, *dir, buffer[1024];
	int cd_r;

	p = getcwd(buffer, 1024);
	if (!p)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			cd_r = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			cd_r = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(p);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		cd_r = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		cd_r = chdir(info->argv[1]);
	if (cd_r == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the current dir
 * @info: Struct consist of potential arg
 *  Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **a_arr;

	a_arr = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*a_arr);
	return (0);
}
