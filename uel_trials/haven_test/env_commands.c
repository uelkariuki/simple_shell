// env_commands.c

#include "main.h"

/*
 * modify_env - modifies the environment variables based on the given command
 */
void modify_env(char *buffer)
{
    char *args[3];
    parse_args(buffer, args);

    if (strncmp(buffer, "setenv", 6) == 0) {
        if (setenv(args[1], args[2], 1) != 0) {
            perror("setenv");
        }
    } else if (strncmp(buffer, "unsetenv", 8) == 0) {
        if (unsetenv(args[1]) != 0) {
            perror("unsetenv");
        }
    }
}

