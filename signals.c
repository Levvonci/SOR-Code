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
#include <signal.h>

int main(int argc, char* argv[]){
  int pid;
  pid = fork();

  if(pid == -1){
    perror("Errore nella fork\n");
    return 1;
  }

  if(pid == 0){
    //figlio
    while(1){
      printf("ciao\n");
      usleep(50000);
    }
  }else{
    //padre
    sleep(1);
    kill(pid, SIGKILL);
    wait(NULL);
  }
  
  return 0;
}
