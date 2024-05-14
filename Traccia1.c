/*
Un processo padre genera due processi figli.
• Il primo processo figlio invia al padre un numero casuale da 0 a 100.
• Il padre legge questo numero, lo moltiplica per un k causale e lo manda al secondo figlio.
• Il secondo figlio legge il numero inviato dal padre e lo stampa a video.
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    int pid1;
    int pid2;

    int fd1[2];
    int fd2[2];

    if (pipe(fd1) == -1) {
        perror("Errore nella creazione della pipe\n");
        return 1;
    }
    if (pipe(fd2) == -1) {
        perror("Errore nella creazione della pipe\n");
        return 2;
    }

    pid1 = fork();
    pid2 = fork();

    if (pid1 == 0) {
        close(fd1[0]);
        close(fd2[0]);
        srand(time(NULL));
        int random = rand() % 101;
        if (write(fd[1], &random, sizeof(int)) == -1) {
            perror("Errore nella scrittura\n");
            return 3;
        }

    } else {
    }

    return 0;
}
