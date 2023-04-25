#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
/**
 * exit_status - envokes exit when user inputs error
 */

void exit_status(char *prompt)
{
	/*exit 98*/
	if (strcmp(prompt, "exit 98") == 0)
	{
		exit(98);
	}
	else if (strcmp(prompt, "exit") == 0)
	{
		printf("exiting program");
		exit(0);
	}
}
