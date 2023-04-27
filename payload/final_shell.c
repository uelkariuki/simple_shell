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

	while (1)
	{
		/*write(STDOUT_FILENO, ":) ", 3);*/
		/*printf(":) ");*/
		if (getline(&command, &buffer_size, stdin) == -1)
		{
			/*printf("shell exit");*/
			/*free(command);*/
			exit(EXIT_SUCCESS);
		}
		if (strcmp(command, "exit\n") == 0)
		{
			free(command);
			break;
		}

		command_tokens = tokenize_command(command);
		exec(command_tokens);
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
