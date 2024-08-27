#include "shell.h"

/**
 * _getenv -get an environment variable
 * @name: name of the environment variable
 *
 * Return: pointer to the value in the environment, or NULL if not found
 */
char *_getenv(const char *name)
{
	int a, len;

	len = strlen(name);
	for (a = 0; environ[a]; a++)
	{
		if (strncmp(name, environ[a], len) == 0 && environ[a][len] == '=')
		{
			return (&environ[a][len + 1]);
		}
	}
	return (NULL);
}

/**
 * check_command_in_path - check if a command exists in a directory
 * @path_token: the directory to check
 * @command: the command to find
 * @path_copy: copy of the path environment variable to free after
 *
 * Return: full path of the command if found, NULL if not found
 *
 */
char *check_command_in_path(char *path_token, char *command, char *path_copy)
{
	char *file_path;
	int command_length, directory_length;
	struct stat buffer;

	command_length = strlen(command);
	directory_length = strlen(path_token);
	file_path = malloc(command_length + directory_length + 2);
	strcpy(file_path, path_token);
	strcat(file_path, "/");
	strcat(file_path, command);

	if (stat(file_path, &buffer) == 0)
	{
		free(path_copy);
		return (file_path);
	}
	free(file_path);
	return (NULL);
}

/**
 * find_command - find the full path of a command
 * @command: command to find
 *
 * Return: full path of the command if found, Null if not found
 *
 */
char *find_command(char *command)
{
	char *path, *path_copy, *path_token;
	struct stat buffer;

	path = _getenv("PATH");
	if (path)
	{
		path_copy = strdup(path);
		path_token = strtok(path_copy, ":");

		while (path_token != NULL)
		{
			char *result = check_command_in_path(path_token, command, path_copy);

			if (result)
				return (result);
			path_token = strtok(NULL, ":");
		}
		free(path_copy);
	}

	if (stat(command, &buffer) == 0)
	{
		return (strdup(command));
	}
	return (NULL);
}
