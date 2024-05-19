#include <stdio.h>
#include <stdlib.h>

int main() {
  int numero;
  FILE *file;

  if ((file = fopen("/Users/lvnc/repo/SOR-Code/prova2.txt", "r")) == NULL) {
    perror("Errore nella lettura\n");
    return 1;
  }

  fscanf(file, "%d", &numero);
  printf("Il valore di numero è: %d\n", numero);
  fclose(file);

  return 0;
}
