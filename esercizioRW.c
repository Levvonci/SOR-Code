/*
Dato un processo padre:
- il figlio genera un file su cui ci scrive un numero
- il padre legge quel numero, lo moltiplica per 2 e lo riscrive sullo stesso file
*/

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    int num;
    int fd = open("/Users/lvnc/repo/SOR-Code/provaEsercizio.txt", O_RDONLY | O_CREAT);
    printf("fd = %d\n", fd);
    if (fd == -1) {
        printf("Errore: %d", errno);
        perror("Program");
    }
    if (close(fd) == -1) {
        printf("Errore: %d", errno);
        perror("Program");
    }
    printf("fd Chiuso\n");
    return 0;
}
