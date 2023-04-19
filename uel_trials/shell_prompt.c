#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "main.h"

/**
 * function description
 */
int main(int ac, char **argv)
{

	/* correction 1 : last two arguments char instead of char * */
	char *com_prompt, *buffer, *buf_copy, *buf_token;
	size_t n = 0;
	ssize_t com_line;
	int count = 0, i, counter;
	/* print command or write exit to reminate*/

	/* prompt text */
	printf("Enter Command to run shell\nEnter ctrl+D to terminate\n");

	/*loop to continually enter command */
	while (1)
	{
		com_prompt = "user/$: ";
		printf("%s", com_prompt);
		
		/* get user input */
		com_line = getline(&buffer, &n, stdin);
		
		/* printing command */
		printf("%s", buffer);

		/*strok and allocation of a copy of buffer)*/
		buf_copy = malloc(sizeof(char) * com_line);
		/*error handle for alloc for buf_copy*/
		if (buf_copy == NULL)
		{
			free(buffer);
			perror("error in allocating space for buffer copy");
			return (-1);
		}

		/* check for error */
		if (com_line == EOF)
		{
			free(buffer);
			return (-1);
		}
		else
		{
			/* copying contents of buffer into buf copy*/
			strcpy(buf_copy, buffer);
			
			/* creating a parsing for our command */
			char *buffer2;
			char *delim = " ";
			buffer2 = strtok(buffer, delim);
			
			while (buffer2 != NULL)
			{
				count++;
				buffer2 = strtok(NULL, delim);
			}
			count++;
			
			argv = (char *) malloc(sizeof(char) * count);
			buf2_size = strlen(buffer2);
			
			/* iterating the command */
			for (i = 0; buffer2 != NULL; i++)
			{
				argv[i] = malloc(sizeof(char) * buf2_size);
				strcpy(argv[i], buffer2);
				buffer2 = strtok(NULL, delim);
			}
			argv[i] = NULL;

			/*check if program works */
			for (counter = 0; counter < count-1; counter++)
			{
				printf("%s\n", argv[i]);
			}
		}
	}
	
	/* free seg*/
	free(buffer);
	return (0);
}
