#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void traitantSIGALRM(int num)
{
	if(num != SIGALRM)
	{
		printf("Mauvais signal (traitantSIGALRM)");
		kill(getpid(), SIGKILL);
	}
	printf("SIGALRM RECU");
}

unsigned int mysleep(unsigned int seconds)
{
	alarm(seconds);
	if (signal(SIGALRM, traitantSIGALRM)==0)
		return 0;
}

int main(int argc, char** argv)
{
	int s=atoi(argv[1]);
	mysleep(s);
	return 0;
}
