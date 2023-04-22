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
		/*for (i = 0; i < 2; i++)
		{
			printf("Enter code: ");
			scanf("%s\n", buffer);
			system(buffer);
		}*/
		printf("Enter command\nUser/$: ");

		if (fgets(buffer, sizeof(buffer), stdin) == NULL)
		{
			break;
		}

		buffer[strcspn(buffer, "\n")] = '\0';
		system(buffer);
	}
	return (0);
}
