#include "shell.h"

/**
 * shell_cd - change directory
 * @args: array of arguments
 *
 * Return: 1 to continue excuting, 0 to exit
 */

int shell_cd(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "shell: expected argument to \"cd\"\n");
	} else
	{
		if (chdir(args[1]) != 0)
		{
			perror("shell");
		}
	}
	return (1);
}

/**
 * shell_exit - exit the shell
 * @args: array of arguments
 *
 * Return: 0 to exit
 *
 */

int shell_exit(char **args)
{
	(void)args;
	return (0);
}

/**
 * shell_env - print environment variables
 * @args: array of arguments
 *
 * Return: 1 to continue executing
 *
 */

int shell_env(char **args)
{
	int a = 0;
	(void)args;

	while (environ[a])
	{
		printf("%s\n", environ[a]);
		a++;
	}
	return (1);
}
