#include "main.h"


int main(int ac __attribute__((unused)), char **av __attribute__((unused)))
{
        char *command = NULL;
        char **command_tokens;
        size_t buffer_size = 0;
        int interactive_mode = 1;
	char *program_name = av[0];

        while (1)
        {
                interactive_mode = isatty(STDIN_FILENO);
                if (interactive_mode)
                {
                        write(STDOUT_FILENO, ":) ", 13);
                }
                if (getline(&command, &buffer_size, stdin) == -1)
                {
                        /*printf("shell exit");*/
                        /*free(command);*/
                        exit(EXIT_FAILURE);
                }
                if (strcmp(command, "exit\n") == 0)
                {
                        free(command);
                        break;
                }

                command_tokens = tokenize_command(command);
		interactive_mode = isatty(STDOUT_FILENO);
		if (!interactive_mode && command_tokens[0] != NULL && access(command_tokens[0], F_OK) == -1)
                {
                        exec(command_tokens, program_name);
                        free(command_tokens);
                }
                else if (command_tokens[0] != NULL)
                {
                        exec(command_tokens, program_name);
                        free(command_tokens);
                }
        }
        return (0);

}

/**
 * tokenize_command - function to tokenize commands
 * @command: the command to be tokenized
 * Return: fully and well tokenized commands
 */

char **tokenize_command(char *command)
{
        char **command_tokens;
        char *token;
        int q = 0;

        command_tokens = malloc(sizeof(char *) * COMMAND_MAX_LENGTH);

        if (command_tokens == NULL)
        {
                perror("malloc failed from tokenize_command");
                exit(EXIT_FAILURE);
        }
        token = custom_strtok(command, " \n");

        while (token != NULL)
        {
                command_tokens[q++] = token;
                token = custom_strtok(NULL, " \n");
        }
        command_tokens[q] = NULL;

        return (command_tokens);


} 
