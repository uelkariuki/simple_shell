#include "main.h"


void execute_command(char **args)
{
    if (strcmp(args[0], "exit") == 0)
    {
        exit(0);
    }
    /*else if (strcmp(args[0], "cd") == 0)
    {
        cd(args);
    }*/
    else if (strcmp(args[0], "setenv") == 0)
    {
        set_env(args);
    }
    else if (strcmp(args[0], "unsetenv") == 0)
    {
        unset_env(args);
    }
    else
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            execvp(args[0], args);
            perror(args[0]);
            exit(1);
        }
        else
        {
            wait(NULL);
        }
    }
}

