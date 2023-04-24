#include "main.h"

int main()
{
    char *line = NULL;
    size_t line_size = 0;
    char *commands[10]; // maximum of 10 commands
    int num_commands;
    int i;

    while (1)
    {
        num_commands = 0;

        printf("Enter command\n:) ");

        if (getline(&line, &line_size, stdin) == -1)
        {
            break;
        }

        if (strcmp(line, "exit\n") == 0)
        {
            printf("Exiting the simple shell...\n");
            printf("Goodbye\n");
            break;
        }

        // split line into commands
        char *token = NULL;
        char *saveptr = NULL;
        token = strtok_r(line, ";", &saveptr);
        while (token != NULL && num_commands < 10)
        {
            commands[num_commands++] = token;
            token = strtok_r(NULL, ";", &saveptr);
        }

        // execute each command
        for (i = 0; i < num_commands; i++)
        {
            // remove leading and trailing whitespace
            char *command = trim(commands[i]);

            // execute command
            system(command);
        }
    }

    free(line);

    return 0;
}

