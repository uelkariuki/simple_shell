#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define BUFSIZE 100
/*function parameters*/
pid_t fork_child(char *buffer);
char error_eof(ssize_t prompt, char *buffer);
void file_path(char *command);
char *strtok(char *str, const char *delim);
int _setenv(const char *name, const char *value, int overwrite);
/* advanced tasks*/
char *without_getline();
void exit_status(char *prompt);
#endif
