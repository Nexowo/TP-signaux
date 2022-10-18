#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void erreur(const char* msg) {

  fprintf(stderr,"%s\n",msg);

  }

void traitantSIGINT(int num) {

  if (num!=SIGINT)
    erreur("Pb sur SigInt...");
  printf("\n---- Ctrl-C interdit -----\n");
  kill(getpid(), SIGKILL);
  }

void traitantSIGTSTP(int num) {
	if (num!=SIGTSTP)
		erreur("pb sur SIGTSTP");
	printf("\nSuspention du processus\n");
}

void hdl (int sig, siginfo_t *siginfo, void *context)
{

    	printf("\n\nNum signal:%i\nPID processus transmetteur:%i\nGroupe du processus:%i\n",siginfo->si_signo, siginfo->si_pid, siginfo->si_uid);
    	pause();
}	
	

int main(int argc,char* argv[]) {

    int s,i;
    if (argc-1 != 1) {
        fprintf(stderr,"Appel : %s <nb de secondes>\n",argv[1]);
        return 1;
        }
    s=atoi(argv[1]);
    signal(SIGINT,traitantSIGINT);
    struct sigaction sig;
    sig.sa_handler = &hdl;
    sigaction(SIGTSTP, &sig, NULL);
    for (i=1;i<=s;i++) {
        sleep(1);
        printf("\r %d secondes ecoules...",i);
        fflush(stdout);               /* force affichage */
    }
    printf("\n");

    return 0;
}

