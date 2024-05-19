/*
 7. Scrivere un programma C che crea un processo figlio.
• Il padre legge una numero casuale e lo invia al figlio attraverso una pipe.
• Il figlio fa il quadrato del numero e lo invia nuovamente al padre solo se il quadrato è pari, attraverso la pipe.
• Il padre legge il numero e lo stampa.
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
    int pid;
    int fd[2];
    if (pipe(fd) == -1) {
        perror("Errore nella pipe\n");
        return 1;
    }

    pid = fork();

    if (pid == 0) {
        int randomPadre;
        if (read(fd[0], &randomPadre, sizeof(int)) == -1) {
            perror("Errore nella lettura del figlio\n");
            return 3;
        }
        int randomPadre2 = randomPadre * randomPadre;
        if (write(fd[1], &randomPadre2, sizeof(int)) == -1) {
            perror("Errore nella scrittura del figlio\n");
            return 4;
        }
        close(fd[1]);
        close(fd[0]);

    } else {
        int random;
        srand(time(NULL));
        random = rand() % 101;
        printf("Il numero iniziale inviato dal padre è: %d\n", random);
        if (write(fd[1], &random, sizeof(int)) == -1) {
            perror("Errore nella scrittura del padre\n");
            return 2;
        }
        close(fd[1]);

        wait(NULL);

        close(fd[1]);
        int randomFiglio;
        if (read(fd[0], &randomFiglio, sizeof(int)) == -1) {
            perror("Errore nella lettura del padre\n");
            return 5;
        }
        printf("Il numero al quadrato da parte del figlio è: %d\n", randomFiglio);
        close(fd[0]);
    }

    return 0;
}
