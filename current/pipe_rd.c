#include "main.h"
#define BUFSIZE 1024
void pipe_rd(int pipepath)
{
	char buffer[BUFSIZE];
	int no_bytes;

	while ((no_bytes = read(pipepath, buffer, BUFSIZE)) > 0)
	{
		if (write(STDOUT_FILENO, buffer, no_bytes) == -1)
		{
			perror("Error: couldn't write");
			exit(EXIT_FAILURE);
		}
	}
	if (no_bytes == -1)
	{
		perror("Error: couldn't read");
		exit(EXIT_FAILURE);
	}

	if (close(pipepath) == -1)
	{
		perror("Error: close");
		exit(EXIT_FAILURE);
	}
}
