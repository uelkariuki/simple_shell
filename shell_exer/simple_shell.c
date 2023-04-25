#include "main.h"

/**
 * main - prints out the results of the user input shell cmd
 * @argc: no of arguments in a argv
 * @argv: array pointer for argc
 * return: 0
 */

int main(int argc, char **argv)
{
	pid_t pid;
	char *buffer, *av[100];
	size_t buffer_size = BUFSIZE;
	int status, executed_execve = 0;
	ssize_t prompt;
	(void)argc;
	(void)argv;
	
	buffer = malloc(sizeof(char) * buffer_size);
	if (buffer == NULL)
	{
		perror("Error: Allocating malloc");
		exit(EXIT_FAILURE);
	}
	else
	{
		while (1)
		{
			printf("$ ");
			/*without getline function*/
			prompt = getline(&buffer, &buffer_size, stdin);
			if (prompt == EOF)
			{
				perror("Error: reached end of file\n");
				free(buffer);
				exit(EXIT_FAILURE);
			}
			
			buffer[strcspn(buffer, "\n")] = '\0';
			/*exit_status function*/
			exit_status(buffer);

			pid = fork();
			if (pid == -1)
			{
				perror("Error: while creating fork");
				exit(EXIT_FAILURE);
			}
			else if (pid == 0)
			{
				av[0] = buffer;
				av[1] = NULL;
				if( execve(av[0], av, NULL) == 1)
				{
					perror("error: executing execve");
					free(buffer);
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				wait(&status);
				if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS)
				{
					executed_execve = 1;
				}
			}
			if (!executed_execve)
			{
				system(buffer);
			}
			else
			{
				executed_execve = 0;
			}
		}
	}
	free(buffer);
	return (0);
}	
