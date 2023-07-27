#include "my_shell.h"

/**
 * handle_arguments - handle arguments
 * @line: string to break down
 * Return: void.
 */
void handle_arguments(char *line)
{
	char *command[1000], *token;
	int i = 0;

	token = strtok(line, " \t\n");
	while (token != NULL)
	{
		command[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	command[i] = NULL;
	if (_strcmp(command[0], "exit") == 0)
	{
		if (i == 1)
		{
			exit(0); 
		}
		else if (i == 2)
		{
			int status = _atoi(command[1]);
			exit(status);
		}
		else
		{
			perror("Usage: exit [status]");
		}
	}
	if (execve_helper(command[0], command) == -1)
	{
		perror("Execve Error");
		return;
	}
}

/**
 * execve_helper - execute the command using execve
 * @command: the command to execute
 * @args: an array of arguments including the command itself
 * Return: void
 */
int execve_helper(char *command, char *args[])
{
	char *command_path = command;

	if (command_path[0] != '/' && command_path[0] != '.')
		command_path = locate_path(command_path);
	if (!command_path || access(command_path, X_OK) == -1)
	{
		if (errno == EACCES)
			exit_status = (handle_error(args, 126));
		else
			exit_status = (handle_error(args, 127));
		retry_with_next_path = 1;
		perror("path error");
		return (-1);
	}

	if (execve(command_path, args, environ) == -1)
		{
			if (errno == EACCES)
				exit_status = (handle_error(args, 126));
		}
		retry_with_next_path = 0;
	}
	while (retry_with_next_path)
		;
	return (exit_status);
			perror("Execve Error");
			return (-1);
		}
		return (0);
}
