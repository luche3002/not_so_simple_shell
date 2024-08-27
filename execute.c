#include "shell.h"

/**
 * execute - execute built-in or external commands
 * @args: array of arguments
 *
 * Return: 1 if the shell should continue, 0 if it ends
 */

int execute(char **args)
{
	int a;
	char *builtin_str[] = {
		"cd",
		"exit",
		"env"
	};
	int (*builtin_func[])(char **) = {
		&shell_cd,
		&shell_exit,
		&shell_env
	};

	if (args[0] == NULL)
	{
		return (1);
	}

	for (a = 0; a < 3; a++)
	{
		if (strcmp(args[0], builtin_str[a]) == 0)
		{
			return ((*builtin_func[a])(args));
		}
	}
	return (launch(args));
}

/**
 * launch - launch an external program
 * @args: array of arguments
 *
 * Return:1 after completed
 */

int launch(char **args)
{
	pid_t pid;
	int status;
	char *command_path;

	command_path = find_command(args[0]);
	if (command_path == NULL)
	{
		fprintf(stderr, "%s: command not found\n", args[0]);
		return (1);
	}

	pid = fork();
	if (pid == 0)
	{
		if (execve(command_path, args, environ) == -1)
		{
			perror("launch");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("launch");
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while
				(!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	free(command_path);
	return (1);
}
