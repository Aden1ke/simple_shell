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
		exit(98);
	}
	if (execve_helper(command[0], command) == -1)
	{
		perror("Execve Error");
		exit(EXIT_FAILURE);
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
		perror("path error");
		exit(EXIT_FAILURE);
	}

	if (execve(command_path, args, environ) == -1)
	{
		perror("Execve Error");
		return (-1);
	}
	return (0);
}
/**
 * _strcmp - function that compares two strings.
 * @s1: pointer to the 1st string.
 * @s2: poniter to the 2nd string.
 * Return: Always 0.
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] != '\0' && s1[i] == s2[i]; i++)
		;
	return (s1[i] - s2[i]);
}
