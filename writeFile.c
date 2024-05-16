#include <stdio.h>
#include <stdlib.h>

int main() {
    int numero;
    FILE *file;

    file = fopen("/Users/lvnc/repo/SOR-Code/prova.txt", "w");
    if (file == NULL) {
        perror("Errore nella creazione del file\n");
        return 1;
    }
    printf("Enter a number: ");
    scanf("%d", &numero);
    fprintf(file, "%d\n", numero);
    fclose(file);
    return 0;
}
