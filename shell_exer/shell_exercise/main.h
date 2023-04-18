#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#ifndef MAIN_H
#define MAIN_H

/**
 */
struct pid_t{
	unsigned int my_pid;
} my_ppid;
/**
 * function prototype
 */
char *strtok(char *str, const char *delim);
#endif
