#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>


int main(int argc, char* argv[]){
  int arr[5];
  int fd = open("somma", O_RDONLY);
  if(fd == -1){
    return 1;
  }
  int i;
  for(i = 0; i < 5; i++){
    if(read(fd, &arr[i], sizeof(int)) == -1){
      return 2;
    }
    printf("Ricevuto %d\n", arr[i]);
  }
  close(fd);

  int somma = 0;
  for(i = 0; i < 5; i++){
    somma += arr[i];
  }
  printf("Il risultato della somma è: %d\n", somma);

  return 0;
}
