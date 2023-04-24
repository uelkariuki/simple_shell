#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>

/*
 * main - finds the path of of the filename
 */

int main()
{
	char buffer[100];

	/*simpler code*/
	while (1)
	{

		printf("Enter command\n:) ");

		if (fgets(buffer, sizeof(buffer), stdin) == NULL)
		{
			break;
		}
		if (strcmp(buffer, "exit\n") == 0)
		{ /*here we check if users input from stdin matches "exit"*/
			printf("Exiting the simple shell...\n");
			printf("Goodbye\n");
			break; /*exit the loop*/
		}

		buffer[strcspn(buffer, "\n")] = '\0';
		system(buffer);
	}
	return (0);
}
