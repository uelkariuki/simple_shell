#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

int main(int ac, char **av)
{
	char *buffer;
	size_t buffer_size = 32;


	(void)ac;


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
		size_t command = getline(&buffer, &buffer_size, stdin);

		printf("%s", buffer);
	}

	return(0);
}
