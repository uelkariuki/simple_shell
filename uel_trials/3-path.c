#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>

/**
 * path_file - prints out the path of the current dir
 */

int path_func_3()
{
	char *buffer, *dir;
	const char *delim = " : ";

	/*path dec*/
	buffer = getenv("PATH");

	if (buffer == NULL)
	{
		fprintf(stderr, "no dir path found");
		exit(0);
	}

	else
	{
		dir = strtok(buffer, delim);
		while (dir != NULL)
		{
			printf("%s\n", dir);
			dir = strtok(NULL, delim);
		}
	}
	return (0);

}
