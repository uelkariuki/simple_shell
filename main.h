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
#include <errno.h>

#define COMMAND_MAX_LENGTH 1024
#define MAX_ALIAS_NAME_LEN 32
#define MAX_ALIAS_VALUE_LEN 128
#define MAX_LINE_LEN 1024
#define MAX_ARGS 64
#define MAX_ALIASES 20

extern char **environ;

char *_getenv(const char *name);
int _unsetenv(const char *name);
int _setenv(const char *name, const char *value, int overwrite);
int pid_func(void);
int ppid(void);
char *custom_strtok(char *string, const char *delimiter);
void modify_env(char *buffer);
char *handle_comments(char *command);
char *find_file_path(char *path, char *cmd);

int main(int ac __attribute__((unused)), char **av __attribute__((unused)));
char *path_func(char *cmd);
char *path_builder(const char *dir, const char *command);
void exec(char **argv, char *program_name);
char **tokenize_command(char *command);
void env_func(void);
char **strtok_cmd(char *command);
int isatty(int fd);
void change_directory(char *path);
void print_alias(char *name);
void print_aliases();
void define_alias(char *name, char *value);
void execute_alias(char **args);
char *get_alias(char *alias_name);
void add_alias(char* alias_name, char* alias_value, int line_num);
typedef struct Alias {
	char name[MAX_ALIAS_NAME_LEN];
	char value[MAX_ALIAS_VALUE_LEN];
	int line_num;
	struct Alias *next;
} Alias;
typedef struct {
	char name[MAX_ALIAS_NAME_LEN];
	char value[MAX_ALIAS_VALUE_LEN];
}  alias_t;
Alias* alias_list;
alias_t aliast_struct[MAX_ALIASES];


#endif
