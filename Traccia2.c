/*
Generare due processi figli che comunicano con il padre.
• Uno dei processi genera numeri casuali [0-100] ed invia al padre solo i numeri pari.
• L’altro processo genera numeri casuali [0-100] ed invia al padre solo i numeri dispari.
• Il padre fa la loro somma e quando la somma > 190, termina l’esecuzione dei figli.
*/

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int pid1;
    int pid2;
    int fd1[2];
    int fd2[2];

    if (pipe(fd1) == -1) {
        perror("Errore nella pipe 1\n");
        return 2;
    }
    if (pipe(fd2) == -1) {
        perror("Errore nella pipe 2\n");
        return 3;
    }

    pid1 = fork();

    if (pid1 == -1) {
        perror("Errore nella fork\n");
        return 1;
    }

    if (pid1 == 0) {
        srand(time(NULL));
        int random1 = 0;
        while (1) {
            random1 = rand() % 101;
            if (random1 % 2 == 0) {
                if (write(fd1[1], &random1, sizeof(int)) == -1) {
                    perror("Errore nella scrittura\n");
                    return 4;
                }
            }
        }
        close(fd1[0]);

    } else {
        int padre1random;
        int padre2random;

        if (read(fd1[0], &padre1random, sizeof(int)) == -1) {
            perror("Errore nella lettura\n");
            return 5;
        }

        pid2 = fork();

        if (pid2 == -1) {
            perror("Errore nella fork\n");
            return 6;
        }

        if (pid2 == 0) {
            srand(time(NULL));
            int random2 = 0;
            while (1) {
                random2 = rand() % 101;
                if (random2 % 2 > 0) {
                    if (write(fd2[1], &random2, sizeof(int)) == -1) {
                        perror("Errore nella scrittura\n");
                        return 7;
                    }
                }
            }
        }
        if (read(fd2[0], &padre2random, sizeof(int)) == -1) {
            perror("Errore nella lettura\n");
            return 8;
        }

        int somma = padre1random + padre2random;
        while (somma < 190) {
            if (somma > 190) {
                kill(SIGKILL, pid1);
                kill(SIGKILL, pid2);
                printf("Somma: %d", somma);
            }
        }
        return 0;
    }
}
