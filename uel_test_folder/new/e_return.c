#include "main.h"

/**
 * exec - function that executes a command
 * @argv: an array containing the program command line arguments
 *
 */



void exec(char **argv, char *program_name)
{
        char *cmd = NULL, *true_cmd = NULL;
        int cs; /*current_state;*/
        pid_t pid;
	int line_num = 1;

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
                                exit(EXIT_FAILURE);
                        }
                }
                else
                {  /* parent process*/
                        if (waitpid(pid, &cs, 0) == -1)
                        {
                                perror("waitpid");
                                exit(EXIT_FAILURE);
                        }
                }
                free(true_cmd);
        }
}   
