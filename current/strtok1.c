#include "main.h"
#define MAX_ARGLMT 64
#define MAX_CHAR 64
/**
 *
 */
char **strtok_cmd(char *command)
{
	const char *delim = " ";
	int i = 0;
	char *arg;

	char **args = (char **)malloc(MAX_ARGLMT * sizeof(char *));
	if (!args)
	{
		perror("Error: couldn't alloc args space");
		exit(EXIT_FAILURE);
	}

	arg = strtok(command, delim);
	while (arg != NULL && i < MAX_ARGLMT - 1)
	{
		args[i] = (char *)malloc(MAX_CHAR * sizeof(char));
		if (!args[i])
		{
			perror("Error: malloc argv[i]");
			exit(EXIT_FAILURE);
		}
		strncpy(args[i], arg, MAX_CHAR - 1);
		i++;
		arg = strtok(NULL, delim);
	}
	args[i] = NULL;

	if (i == 0)
	{
		args[0] = (char *)malloc(MAX_ARGLMT * sizeof(char));
		if (!args[0])
		{
			perror("Error: malloc in string");
			exit(EXIT_FAILURE);
		}
		strncpy(args[0], command, MAX_ARGLMT - 1);
		args[i] = NULL;
	}

	return args;
}

