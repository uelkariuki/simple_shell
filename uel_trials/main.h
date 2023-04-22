#ifndef MAIN_H
#define MAIN_H

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

char *_getenv(const char *name);
int _unsetenv(const char *name);
int _setenv(const char *name, const char *value, int overwrite);
int pid_func(void);
int ppid(void);

typedef struct node {
	char *dir;
	struct node *next;
} node_t;

node_t *path_list_func(void);

/*alias our_aliases[] = {
	{"ls", "ls - color=auto"},
	{"ll", "ls -aLF"};
	{"la", "ls -A"};
	{NULL,NULL},
} our_aliases;*/


#endif 
