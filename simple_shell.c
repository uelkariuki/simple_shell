#include "main.h"
/**
 * main - prints out the results of the user input shell cmd
 * @argc: no of arguments in a argv
 * @argv: array pointer for argc
 * Return - 0 on success and non-sero on failure
 */
int main(int argc, char **argv)
{
	char *buffer, *token, *delim = " ";
	size_t bufsize = 0;
	int status;
	ssize_t prompt;
	pid_t pid;

	buffer = malloc(sizeof(char) * bufsize);

	if (buffer == NULL)
	{
		perror("Error: Allocating malloc");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		printf("$ ");
		prompt = getline(&buffer, &bufsize, stdin);

		if (prompt == EOF)
		{
			printf("end of file\n");
			free(buffer);
			exit(EXIT_FAILURE);
		}

		buffer[strcspn(buffer, "\n")] = '\0';

		/*exit_status(buffer);*/
		if (strlen(buffer) == 0)
		{
			continue;
		}

		argc = 0;
		token = strtok(buffer, delim);
		while (token != NULL && argc < 99)
		{
			argv[argc++] = token;
			token = strtok(NULL, delim);
		}
		argv[argc] = NULL;
		pid = fork();
		if (pid == -1)
		{
			perror("Error: while creating fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if( execve(argv[0], argv, NULL) == -1)
			{
				if (errno == ENOENT)
				{
					printf("%s: No such file or directory\n", argv[0]);
					free(buffer);
					exit(EXIT_FAILURE);
				}
				perror("error: executing execve");
				free(buffer);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(&status);
		}
	}
	free(buffer);
	return (0);
}
