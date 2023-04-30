#include "main.h"

#define COMMAND_MAX_LENGTH 1024

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
	int i_mode = 1, status, line_nbr = 1;
	char *program_name = av[0];

	while (1)
	{
		i_mode = isatty(STDOUT_FILENO);
		if (i_mode)
		{
			write(STDOUT_FILENO, "", 1);
		}
		if (getline(&command, &buffer_size, stdin) == -1)
		{
			free(command);
			exit(EXIT_SUCCESS);
		}
		if (command[0] == '#')
		{
			continue;
		}
		if (strcmp(command, "exit\n") == 0 || strcmp(command, "exit 0\n") == 0)
		{
			free(command);
			exit(EXIT_SUCCESS);
		}
		if (strncmp(command, "exit ", 5) == 0)
		{
			status = atoi(command + 5);

			if ( status >= 0)
			{
				free(command);
				exit(status);
			}
			else
			{
				fprintf(stderr, "%s: %d: exit: Illegal number: %d\n", program_name, line_nbr, status);
				free(command);
				exit(2);
			}
		}
		command_tokens = tokenize_command(command);
		i_mode = isatty(STDOUT_FILENO);
		if (!i_mode && command_tokens[0] != NULL
				&& access(command_tokens[0], F_OK) == -1)
		{
			exec(command_tokens, program_name);
			free(command_tokens);
		}
		else if (command_tokens[0] != NULL)
		{
			exec(command_tokens, program_name);
			/*free(command_tokens);*/
		}
		else if (strcmp(command_tokens[0], "cd") == 0)
		{
			if (command_tokens[1] == NULL)
			{
				chdir(getenv("HOME"));
			}
			else if (strcmp(command_tokens[1], "-") == 0)
			{
				char *prev_dir = getenv("OLDPWD");
				if (prev_dir == NULL)
				{
					fprintf(stderr, "cd: OLDPWD not set\n");
				}
				else
				{
					if (chdir(prev_dir) != 0)
					{
						perror("cd");
					}
					else
					{
						printf("%s\n", prev_dir);
					}
				}
			}
			else
			{
				if (chdir(command_tokens[1]) != 0)
				{
					perror("cd");
				}
				else
				{
					setenv("OLDPWD", getenv("PWD"), 1);
					setenv("PWD", getcwd(NULL, 0), 1);
					printf("%s\n", getenv("PWD"));
				}
			}
			continue;
		}
		/*else if (strcmp(command_tokens[0], "alias") == 0)
		{
			execute_alias(command_tokens);
		}*/
		
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
	char *token, *var_start, *var_end, *var_name, *var_value;
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
		if (token[0] == '#')
		{
			break;
		}
		
		var_start = strchr(token, '$');
		
		if (var_start == NULL)
		{
			command_tokens[q++] = token;
			token = custom_strtok(NULL, " \n");
			continue;
		}
		
		var_end = var_start + 1;
		
		while (*var_end && (*var_end != '$') && (*var_end != ' '))
		{
			var_end++;
		}
		
		var_name = strndup(var_start + 1, var_end - var_start - 1);
		
		if (strcmp(var_name, "?") == 0)
		{
			var_value = strerror(errno);
		}
		
		else if (strcmp(var_name, "$$") == 0)
		{
			var_value = malloc(sizeof(char) * 16);
			snprintf(var_value, 16, "%d", getpid());
		}
		else
		{
			var_value = getenv(var_name);
		}
		
		if (var_value != NULL)
		{
			*var_start = '\0';
			command_tokens[q++] = token;
			command_tokens[q++] = var_value;
			token = var_end;
		}
		else
		{
			command_tokens[q++] = token;
			token = custom_strtok(NULL, " \n");
		}
		free(var_name);
	}
	command_tokens[q] = NULL;
	return (command_tokens);
}
