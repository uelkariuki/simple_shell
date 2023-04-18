#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include <unistd.h>
/**
 * PID
 */

int main(void)
{
	pid_t my_pid;
	my_pid = getpid();
	printf("%u\n", my_pid);
	return (0);
}

