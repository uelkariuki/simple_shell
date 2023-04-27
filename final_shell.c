#include "main.h"

/**
 * main - main shell program
 * @ac: number of command line arguments
 * @av: an array containing the program command line arguments
 * Return: 0
 */


int main(int ac __attribute__((unused)), char **av __attribute__((unused)))
{
	char *command = NULL;
	char **command_tokens;
	size_t buffer_size = 0;
	int i_mode /* interactive mode*/, line_num = 1;

	while (i_mode)
	{
		if (i_mode == 1)
		{
			write(STDOUT_FILENO, ":) ", 3);
		}
		if (getline(&command, &buffer_size, stdin) == -1)
		{
			exit(EXIT_SUCCESS);
		}
		if (strcmp(command, "exit\n") == 0)
		{
			free(command);
			break;
		}
		command_tokens = tokenize_command(command);
		i_mode = isatty(STDIN_FILENO);
		if (!i_mode && command_tokens[0] != NULL && 
				access(command_tokens[0], F_OK) == -1)
		{
			fprintf(stderr, "%s: %d: %s: not found\n",
					av[0], line_num, command_tokens[0]);

		}
		else
		{
			exec(command_tokens);
		}
		free(command_tokens);
	}
	return (0);


}

/**
 * tokenize_command - function to tokenize commands
 * @command: the command to be tokenized
 * Return: fully and well tokenized commands
 */

char **tokenize_command(char *command)
{
	char **command_tokens;
	char *token;
	int q = 0;

	command_tokens = malloc(sizeof(char *) * COMMAND_MAX_LENGTH);

	if (command_tokens == NULL)
	{
		perror("malloc failed from tokenize_command");
		exit(EXIT_FAILURE);
	}
	token = custom_strtok(command, " \n");

	while (token != NULL)
	{
		command_tokens[q++] = token;
		token = custom_strtok(NULL, " \n");
	}
	command_tokens[q] = NULL;

	return (command_tokens);


}
