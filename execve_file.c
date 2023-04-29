#include "main.h"

/**
 * exec - function that executes a command
 * @argv: an array containing the program command line arguments
 * @program_name: the name of the program
 */

void exec(char **argv, char *program_name)
{
	char *cmd = NULL, *true_cmd = NULL;
	int line_num = 1, cs; /*current_state;*/ 
	pid_t pid;

	if (argv)
	{
		cmd = argv[0];
		if (strcmp(cmd, "env") == 0)
		{
			env_func();
			return;
		}
		true_cmd = path_func(cmd);
		if (true_cmd == NULL)
		{
			fprintf(stderr, "%s: %d: %s: not found\n", program_name, line_num, argv[0]);
			exit(2);
		}
		pid = fork();
		if (pid == -1) /* child process failure*/
		{
			perror("There is an error in pid");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if (execve(true_cmd, argv, environ) == -1)
			{
				fflush(stdout);
				exit(2);
			}

		}
		else
		{  /* parent process*/
			if (waitpid(pid, &cs, 0) == -1)
			{
				perror("waitpid");
				exit(WEXITSTATUS(cs));
			}
			else if (WIFSIGNALED(cs))
			{
				WEXITSTATUS(cs);
				
			}
		}
	}
	free(true_cmd);
}
