#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	pid_t my_pid, p_pid;

	my_pid = getpid();
	p_pid = getppid();
	printf("child: %u\n parent: %u\n", my_pid, p_pid);
	return (0);
}
