#include "main.h"
/**
 * exit_status - envokes exit when user inputs error
 * @prompt: string pointer
 */

void exit_status(char *prompt)
{
	/*exit 98*/
	if (strcmp(prompt, "exit 98") == 0)
	{
		printf("\n");
		exit(98);
	}
	else if (strcmp(prompt, "exit") == 0)
	{
		printf("exiting program\n");
		exit(0);
	}
}
