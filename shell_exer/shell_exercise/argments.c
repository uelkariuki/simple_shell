#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "main.h"

/*
 */
int main(int ac, char **argv)
{
	int i;
	(void)ac;
	char *buffer, *token;
	size_t bufsize = 20;
	const char *delim = " ";


	/* allocate space */
	buffer = (char *) malloc(sizeof(char) * bufsize);

	/*error in allocation*/
	if (buffer == NULL)
	{
		perror("not allocated");
		return (-1);
	}

	/*allocation successful*/
	else
	{
		while (1)
		{
			printf("Enter command & to exit (ctrl + D)\nroot/user/$: ");
			ssize_t command = getline(&buffer, &bufsize, stdin);
			
			/*EOF*/
			if (command == EOF)
			{
				free(buffer);
				printf("\nExiting program....\n");
				return (-1);
			}

			/* parsing center */
			/*int count = strlen(buffer);*/

			/*replacing newline character with null character*/
			buffer[strcspn(buffer, "\n")] = '\0';

			/* iteration for token*/
			for (i = 0; i < ac; i++)
			{
				delim = argv[i];
				token = strtok(buffer, delim);
				while (token != NULL)
				{
					printf("%s", token);
					token = strtok(NULL, delim);
				}
				printf("\n");
			}
			/*printf("%s", token);*/
		}
	}
	free(buffer);
	return (0);
}
