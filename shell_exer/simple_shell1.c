#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include "main.h"

int main(void)
{
	char *buffer = NULL;
	ssize_t prompt = 0;
	size_t bufsize = 32;

	/*struct section*/
	pid_t pid;

	/*buffer alloc*/
	buffer = (char *) malloc(sizeof(char) * bufsize);

	if (buffer == NULL)
	{
		perror("Error: could'nt allocate space\n");
		return (-1);
	}

	/* user prompt*/
	printf("Enter command to exec & ctrl+D to exit\n");
	
	/*iterate program*/
	while (1)
	{
		printf("$ ");
		prompt = getline(&buffer, &bufsize, stdin);

		/*EOF*/
		if (prompt == -1)
		{
			perror("Error: reached end of file\n");
			free(buffer);
			exit(EXIT_FAILURE);
		}
		else
		{
			/* copy terminate new line*/
			buffer[strcspn(buffer, "\n")] = '\0';

			/*fork*/
			pid = fork();

			/*if error in fork*/
			if (pid == -1)
			{
				perror("Error: creating processes\n");
				free(buffer);
				exit(EXIT_FAILURE);
			}

			/* child process*/
			else if (pid == 0)
			{
				/*execute code*/
				char *args[2];
				args[0] = buffer;
				args[1] = NULL;

				/*execve*/
				if (execve(args[0], args, NULL) == -1)
				{
					perror("Error: executing execve");
					free(buffer);
					exit(EXIT_FAILURE);
				}
			}

			/*parent process*/
			else
			{
				wait(NULL);
			}

		}

	}
	return (0);
}
