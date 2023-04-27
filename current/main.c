#include "main.h"
#define BUFSIZE 1024
#define MAXIMUM_ARG 128
/**
 *main - prints out unix shell cmd from user input
 *@argc: no. of arguments
 *@argv: pointer array arguments
 *Return: 0 if success and -1 on failure
 */
int main(int argc, char **argv, char **envp)
{
	int status, no_args = 0, no_args1 = 0, no_args2 = 0;
	char *args[MAXIMUM_ARG], *args2[MAXIMUM_ARG], command[BUFSIZE], *pipe_token, *token;
	char *command1, *command2, buffer;
	pid_t pid;

	while (1)
	{
		/*user prompt*/
		printf("$ ");
		fflush(stdout);

		/*EOF*/
		if (!fgets(prompt, BUFSIZE, stdin))
		{
			printf("\n");
			break;
		}
		/*remove and replace new line*/
		prompt[strcspn(prompt, "\n")] = 0;
		
		pipe_token = strtok(command, "|");
		if (pipe_token == NULL)
		{
			token = strtok(command, " ");
			while (token != NULL && no_args < MAXIMUM_ARG - 1)
			args[no_args++] = token;
			token = strtok(NULL, " ");
			
			args[no_args] = NULL;
			
			/*fork sec*/
			if (no_args > 0)
			{
				pid = fork();
				if (pid == -1)
				{
					perror("Error: fork");
					exit(EXIT_FAILURE);
				}
			}
			else if (pid == 0)
			{
				execute(args, envp);
			}
			else
			{
				waitpid(pid, &status, 0);
			}
		}
		else
		{
			command1 = strtok(pipe_token, " ");
			token = strtok(NULL, " ");
			while (token != NULL && no_args1 < MAXIMUM_ARG - 1)
			{
				args[no_args1++] = token;
				token = strtok(NULL, " ");
			}
			args[no_args1] = NULL;

			command2 = strtok(pipe_token, " ");
			while (token != NULL && no_args2 < MAXIMUM_ARG - 1)
			{
				args[no_args2++] = token;
				token = strtok(NULL, " ");
			}
			args[no_args2] = NULL;

			if (no_args1 > 0 && no_args2 > 0)
			{
				pipe_rd(args, args2, envp);
			}
		}
	}
	return (0);
}
