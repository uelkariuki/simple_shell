#include "main.h"

/**
 * exec - function that executes a command
 * @argv: an array containing the program command line arguments
 * @program_name: the name of the program
 */
#define MAX_LENGTH 1024
void exec(char **argv, char *program_name)
{
	char *cmd = NULL, *true_cmd = NULL;
	int line_num = 1, cs;/*current_state;*/
	pid_t pid;
	int exit_status = 0, status;

	if (argv)
	{
		
		/*special characters*/
		cmd = argv[0];
		if (strcmp(cmd, "env") == 0)
		{
			env_func();
			return;
		}
		else if (strcmp(cmd, "cd") == 0)
                {
                        if (argv[1] == NULL)
                        {
                                change_directory(getenv("HOME"));
                        }
                        else
                        {
                                change_directory(argv[1]);
                        }
                        return;
                }
		else if (strcmp(cmd, "echo") == 0)
		{
			if (strcmp(argv[1], "$?") == 0)
			{
				printf("%d\n", exit_status);
				return;
			}
			else if (strcmp(argv[1], "$$") == 0)
			{
				printf("%d\n", getpid());
				return;
			}
		}
		/*alias*/
		/*else if (strcmp(cmd, "alias") == 0)
		{
			execute_alias(argv);
			if (strcmp(argv[1], "ls") == 0 || strcmp(argv[1], "ls -p") == 0)
			{
				cmd = argv[1];
			}
			else
			{
				cmd = get_alias(argv[0]);
			}
		}
		else
		{
			cmd = get_alias(argv[0]);
		}*/
		
		true_cmd = path_func(cmd);
		if (true_cmd == NULL)
		{
			fprintf(stderr, "%s: %d: %s: not found\n", program_name, line_num, argv[0]);
			exit(1);
		}
		pid = fork();
		if (pid == -1) /* child process failure*/
		{
			perror("There is an error in pid");
			exit(1);
		}
		else if (pid == 0)
		{
			if (execve(true_cmd, argv, environ) == -1)
				fflush(stdout);
		}
		else
		{  /* parent process*/
			if (waitpid(pid, &cs, 0) == -1)
			{
				perror("waitpid");
				exit(1);
			}
			if (WIFEXITED(cs))
			{
				if (WEXITSTATUS(cs))
				{
					status = WEXITSTATUS(cs);
				}
			}
		}
		if (strcmp(argv[1], "&&") == 0 && status == 0)
		{
			exec(&argv[2], program_name);
		}
	}
	free(true_cmd);
}
void change_directory(char *path)
{
	char cwd[MAX_LENGTH];
	if(path == NULL)
	{
		if (chdir(getenv("HOME")) != 0)
		{
			perror("cd");
		}
	}
	else if (strcmp(path, "-") == 0)
	{
		char *prev = getenv("OLDPWD");
		if (prev == NULL)
		{
			fprintf(stderr, "cd: OLDPWD not found");
		}
		else
		{
			if (chdir(prev) != 0)
			{
				perror("cd");
			}
			printf("%s\n", prev);
		}
	}
	else
	{
		if (chdir(path) != 0)
		{
			perror("cd");
		}
		else
		{
			if (getcwd(cwd, sizeof(cwd)) != NULL)
			{
				printf("%s\n", cwd);
				setenv("OLDPWD", getenv("PWD"), 1);
				setenv("PWD", cwd, 1);
			}
			else
			{
				perror("getcwd");
			}
		}
	}
}
