#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void handle_sigtstp(int sig) {
    printf("Non puoi stoppare\n");
}

void handle_sigcont(int sig) {
    printf("Inserisci un numero: ");
    fflush(stdout);
}

int main(int argc, char *argvv[]) {
    struct sigaction sa;
    sa.sa_handler = &handle_sigtstp;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGCONT, &sa, NULL);

    // signal(SIGTSTP, &handle_sigtstp);

    int x;
    printf("Inserisci un numero: ");
    scanf("%d", &x);
    printf("Il risultato di %d * 5 = %d\n", x, x * 5);

    return 0;
}
