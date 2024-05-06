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
  int p1[2];
  
  if(pipe(p1) == -1){ return 1; }
  
  int pid = fork();
  
  if(pid == -1){ return 2; }
  if(pid == 0){
    //figlio
    int x;
    
    close(p1[1]);
    if(read(p1[0], &x, sizeof(x)) == -1){ return 3; }
    printf("Ricevuto: %d\n", x);
    x *= 4;
    
    if(write(p1[1], &x, sizeof(x)) == -1){ return 4; }
    printf("Scritto: %d\n", x);
    close(p1[1]);
    close(p1[0]);
    
  }else{
    //padre
    
    srand(time(NULL));
    int y = rand() % 10;
    
    if(write(p1[1], &y, sizeof(y)) == -1){ return 5; }
    printf("Scritto: %d\n", y);
    
    if(read(p1[0], &y, sizeof(y)) == -1){ return 6; }
    printf("Il risultato è: %d\n", y);
    wait(NULL);
    
    close(p1[1]);
  }
  close(p1[0]);
  close(p1[1]);
  
  return 0;
}
