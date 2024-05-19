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
  
  if((mkfifo("testFifo.txt", 0777)) == -1){
    if(errno != EEXIST){
      printf("Impossibile creare FIFO\n");
      return 1;
    }
  }
  printf("Aprendo...\n");
  int fd = open("testFifo.txt", O_WRONLY);
  
  if(fd == -1){
    return 3;
  }
  
  printf("Aperto\n");
  int x = 100;
  if(write(fd, &x, sizeof(int)) == -1){
    return 2;
  }
  printf("Scrivendo...");
  close(fd); 
  printf("Chiuso...");
  return 0;
}
