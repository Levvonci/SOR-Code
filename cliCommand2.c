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
  int pid = fork();
  if(pid == -1){
    perror("Errore nella fork\n");
    return 1;
  }
  
  if(pid == 0){

    int err = execlp("ping", "ping", "-c", "3", "google.com", NULL);
    if(err == -1){
      printf("Non ho trovato nessun programma da eseguire\n");
      return 2;
    }

  }else{
    
    int wstatus;
    wait(&wstatus);
    if(WIFEXITED(wstatus)){
      int statusCode = WEXITSTATUS(wstatus);
      if(statusCode == 0){
        printf("Successo\n");
      }else{
        printf("Fallimento con status: %d\n", &statusCode);
      }
    }
    printf("Qualcos altro\n");

  }

  return 0;
}
