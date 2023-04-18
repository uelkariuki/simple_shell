#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "main.h"

/**
 * main - prints the system command
 * Return: -1 if there's a fork failure else 0
 */

int main()
{
	/*declaralization */
	int status;
	int i = 0, n = 5;
	pid_t pid;

	/*fork*/
	pid = fork();

	for (; i < n; i++)
	{
		if (pid == -1)
		{
			perror("error creating fork");
			return (-1);
		}
		
		/*child*/
		
		if (pid == 0)
		{
			system("ls -l /tmp");
			return (0);
		}
		
		/*parent*/
		else
		{
			wait(&status);
			system("cat super_shell.c");
		}
	}
	return (0);
}
