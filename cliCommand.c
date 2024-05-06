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
  
  int pid;
  if((pid = fork()) == 0){

    execlp("ping", "ping", "-c", "3", "google.it", NULL);

  }else{
    wait(NULL);
    printf("Successo!!");

  }
  
  
  

  return 0; 
}
