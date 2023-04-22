#include "main.h"

int arg_func(int ac, char **av)
{
	char *buffer;
	size_t buffer_size = 32;
	size_t command;

	(void)ac;
	(void)av;

	buffer = (char *) malloc(buffer_size * sizeof(char));

	if (buffer == NULL)
	{
		perror("unable to allocate memory");
		return (-1);
	}


	printf("enter command, and use exit to exit the program\n");
	while (1)
	{
		printf("/$: Enter command: ");
		command = getline(&buffer, &buffer_size, stdin);

		printf("%s", buffer);
	}

	return(command);
}
