#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main_adv.h"
/**
 * exit_status - envokes exit when user inputs error
 */

void exit_status(char *prompt)
{
	/*exit 98, 99,100*/

	/*exit 98*/
	if (strcmp(prompt, "exit 98") == 0)
	{
		printf("i am exiting coz 0f 98\n");
		exit(98);
	}

	else if (strcmp(prompt, "exit 99") == 0)
	{
		printf("i am exiting coz 0f 99\n");
		exit(99);
	}

	else if (strcmp(prompt, "exit 100") == 0)
	{
		printf("i am exiting coz 0f 100\n");
		exit(100);
	}
}
