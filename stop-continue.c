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

int main(int argc, char *argv[]) {
    int pid;
    pid = fork();

    if (pid == -1) {
        perror("Errore nella fork()\n");
        return 1;
    }
    if (pid == 0) {
        while (1) {

            printf("PorcoDio\n");
            fflush(stdout);
            usleep(50000);
        }
    } else {
        kill(pid, SIGSTOP);
        int t;
        do {
            printf("Tempo di esecuzione: ");
            scanf("%d", &t);

            if (t > 0) {
                kill(pid, SIGCONT);
                sleep(t);
                kill(pid, SIGSTOP);
            }

        } while (t > 0);

        kill(pid, SIGKILL);
        wait(NULL);
    }

    return 0;
}
