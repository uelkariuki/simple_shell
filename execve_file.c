#include "main.h"

/**
 * exec - function that executes a command
 * @argv: an array containing the program command line arguments
 * @program_name: the name of the program
 */

void exec(char **command_tokens, char *program_name)
{
	char *cmd = NULL, *true_cmd = NULL;
	int line_num = 1, cs; /*current_state;*/ 
	pid_t pid;
	char **argv = NULL;

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
			waitpid(pid, &cs, 0);
			if (WIFEXITED(cs))
			{
				/*perror("waitpid");*/
				exit(WEXITSTATUS(cs));
			}
			else if (WIFSIGNALED(cs))
			{
				fprintf(stderr, "%s: %d: %s: terminated by signal %d\n", program_name, line_num, command_tokens[0], WTERMSIG(cs));
			}
		}
	}
	free(true_cmd);
}
