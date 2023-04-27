#ifndef MAIN_H

#define MAIN_H

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <ctype.h>
#include <limits.h>

#define COMMAND_MAX_LENGTH 1024

extern char **environ;
int main(int argc, char **argv, char **envp);
/* trials*/
char **strtok_cmd(char *command);
int pipe_rd(char **command1, char **command2, char **envp);
int execute(char **command, char **envp);

#endif
