#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <time.h>

int main(int argc, char* argv[]){
  
  int arr[5];
  srand(time(NULL));
  int i;
  for(i = 0; i < 5; i++){
    arr[i] = rand() % 100;
  }

  int fd = open("somma", O_WRONLY);
  if(fd == -1){
    printf("Errore fd");
    return 1;
  }
  for(i = 0; i < 5; i++){
    if(write(fd, &arr[i], sizeof(int)) == -1){
      printf("Errore nella scrittura");
      return 2;
    }
    printf("Scritto %d\n", arr[i]);
  }
   close(fd);
  
  return 0;
}
