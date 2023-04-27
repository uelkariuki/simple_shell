#include "main.h"
/**
 *main - prints results of shell cmd entered by user
 *@args: pointer array for holding commands
 *Return: if successful 0, and unsuccessful -1
 */
int main(int argc, char **argv)
{
	size_t bufsize = 100;
	char *buffer, *token, *args[100] = { NULL }, *delim = " ", *dir, *cmd, *pathlk = getenv("PATH");
	ssize_t prompt;
	int status, i = 0, executed_execve = 0, exist_path = 0;
	pid_t pid;
	(void)argc, (void)argv;

	buffer = malloc(sizeof(char) * bufsize);
	if (buffer == NULL)
	{
		perror("Error: Allocating space");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		printf("$ ");
		prompt = getline(&buffer, &bufsize, stdin);

		if (prompt == EOF)
		{
			perror("end of line");
			free(buffer);
			exit(EXIT_FAILURE);
		}
		token = strtok(buffer, delim);
		while (token != NULL)
		{
			args[i] = token;
			token = strtok(NULL, delim);
			i++;
		}
		args[i] = NULL;
		exit_status(argv[0]);

		if (pathlk == NULL)
		{
			perror("Error: no such path");
			free(buffer);
			exit(EXIT_FAILURE);
		}

		dir = strtok(pathlk, ":");
		while (dir != NULL)
		{
			cmd = malloc(strlen(dir) + strlen(argv[0]) + 2);
			if (cmd == NULL)
			{
				perror("Error: couldn't allocate space");
				free(buffer);
				exit(EXIT_FAILURE);
			}
			sprintf(cmd, "%s%s", dir, argv[0]);
			if (access(cmd, X_OK) == 0)
			{
				exist_path = 1;
				break;
			}
			free(cmd);
			dir = strtok(NULL, ":");
		}
		if (exist_path)
		{
			pid = fork();
			if (pid == -1)
			{
				perror("Error: fork");
				free(buffer);
				exit(EXIT_FAILURE);
			}
			else if (pid == 0)
			{
				execve(args[0], args, NULL);
				perror("Error: unsuccessful in execve");
				free(buffer);
				exit(EXIT_FAILURE);
			}
			else
			{
				waitpid(pid, &status, 0);
				if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS)
				{
					executed_execve = 1;
				}
			}
			if (!executed_execve)
			{
				if (system(buffer) == -1)
				{
					perror("error: didnt complete system");
				}
			}
			else
			{
				executed_execve = 0;
			}
			i = 0;
		}
	}
	free(buffer);
	return (0);
}
