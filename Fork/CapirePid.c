#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){

  int id = fork();
  if(id == 0){

    sleep(1);
  }

  printf("Pid Figlio: %d, Pid Padre: %d\n", getpid(), getppid());

  int res = wait(NULL);
  if(res == -1){

    printf("Nessun figlio da aspettare\n");
  }else{

    printf("%d ha finito", res);
  }

  return 0;
}
