#include "main.h"

int main(int ac __attribute__((unused)), char **av __attribute__((unused)))
{
        char *command = NULL;
        char **command_tokens;
        size_t buffer_size = 0;
        int i_mode = 1;

        if (!isatty(STDIN_FILENO)) {
            // Input is coming from a pipe/file
            ssize_t read_size = 0;
            char buffer[1024];
            while ((read_size = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
                buffer[read_size] = '\0';
                command = realloc(command, buffer_size + read_size + 1);
                if (command == NULL) {
                    perror("realloc failed");
                    exit(EXIT_FAILURE);
                }
                memcpy(command + buffer_size, buffer, read_size + 1);
                buffer_size += read_size;
            }
            if (read_size == -1) {
                perror("read failed");
                exit(EXIT_FAILURE);
            }
        }

        while (1)
        {
                if (i_mode)
                {
                        write(STDOUT_FILENO, "$ ", 2);

                }
                if (command == NULL) {
                    if (getline(&command, &buffer_size, stdin) == -1)
                    {
                            /*printf("shell exit");*/
                            /*free(command);*/
                            exit(EXIT_FAILURE);
                    }
                }
                if (strcmp(command, "exit\n") == 0)
                {
                        free(command);
                        break;
                }

                command_tokens = tokenize_command(command);
                i_mode = isatty(STDOUT_FILENO);
                if (!i_mode && command_tokens[0] != NULL && access(command_tokens[0], F_OK) == -1)
                {
                        fprintf(stderr, "%s: %s: command not found\n", av[0], command_tokens[0]);
                }
                else
                {
                        exec(command_tokens);
                        free(command_tokens);
                }
                free(command);
                command = NULL;
                buffer_size = 0;
        }
        return (0);

}

